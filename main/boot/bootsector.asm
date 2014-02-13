; Tell the Assembler that are loaded at offset 0x7c00
[org 0x7c00]
[bits 16]

jmp start					; Jump over the BPB directly to start of the boot loader
nop                         ; This padding of 1 additional byte is needed, because the
							; BPB starts at offset 0x03 in the boot sector

;*********************************************
;	BIOS Parameter Block (BPB) for FAT12
;*********************************************

bpbOEM					db "KAOS    "
bpbBytesPerSector:  	DW 512
bpbSectorsPerCluster: 	DB 1
bpbReservedSectors: 	DW 1
bpbNumberOfFATs: 		DB 2
bpbRootEntries: 		DW 224
bpbTotalSectors: 		DW 2880
bpbMedia: 				DB 0xF0
bpbSectorsPerFAT: 		DW 9
bpbSectorsPerTrack: 	DW 18
bpbHeadsPerCylinder: 	DW 2
bpbHiddenSectors: 		DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber: 	        DB 0
bsUnused: 				DB 0
bsExtBootSignature: 	DB 0x29
bsSerialNumber:	        DD 0xa0a1a2a3
bsVolumeLabel: 	        DB "KAOS DRIVE "
bsFileSystem: 	        DB "FAT12   "

; Start of the boot loader code
start:
	; Setup the ds register
	mov ax, 0
	mov ds, ax

	; Prepare the stack
	mov bp, 0x8000
	mov sp, bp

	; Set the video mode to 80x25
	; This is needed afterwards so that we can print out data
	; in the Protected Mode through 0xB8000
	mov ah, 00h
	mov al, 03h
	int 0x10

	call LoadRootDirectory

	; Read the 2nd sector
	; Here is our C kernel stored
	; mov bx, KERNEL_OFFSET				; Load 1 sector to 0x000 (ES):0x1000 (BX)
	; mov dh, NUMBER_OF_SECTORS_TO_READ	; Load n sectors
	; mov dl, [BOOT_DRIVE]				; Select the boot drive
	; mov cl, 0x02						; Start reading at the 2nd sector (directly after the boot sector)
	; call disk_load						; Perform the I/O operation

	; Print out the welcome message
	; mov ah, 0x0e
	; mov si, welcome_message
	; call printline

	; Print out the loaded data
	; mov ah, 0x0e
	; mov si, ROOTDIRECTORY_OFFSET
	; call printline

	; Switch to protected mode
	call switch_to_protected_mode

	jmp $

;=============================================
; Input String is in register "si"
;=============================================
printline:
	mov al, [si]
	cmp al, 0
	je end_printline

	int 0x10
	inc si
	jmp printline

	end_printline:
ret

;======================================================
; Loads data from the disk
; dh: number of the sectors we want to read
; cl: number of the sector were we will start to read
;======================================================
disk_load:
	push dx

	mov		ah, 0x02					; BIOS read selector function
	mov		al, dh						; Number of the sector we want to read
	mov		ch, BYTE [Track]		    ; Track
	mov		cl, BYTE [Sector]			; Sector
	mov		dh, BYTE [Head]			    ; Head
	mov		dl, [BOOT_DRIVE]			; Select the boot drive
	int		0x13						; BIOS interrupt that triggers the I/O

	jc		disk_error					; Error handling

	pop		dx
	cmp		dh, al						; Do we have read the amount of sectors that we have expected
	jne		disk_error
	ret

;=============================================
disk_error:
	mov ah, 0x0e
	mov si, disk_read_error_message
	call printline
	jmp $

;=========================================================
; Implementation of a simple FAT12 driver that is able
; to load the C kernel file from the file system
;=========================================================
LoadRootDirectory:
	; In the first step we calculate the size (number of sectors) 
	; of the root directory and store the value in the CX register
	; Calculation: 32 * bpbRootEntries / bpbBytesPerSector
	xor     cx, cx
	xor     dx, dx
	mov     ax, 0x0020                      ; 32 byte directory entry
	mul     WORD [bpbRootEntries]           ; total size of directory
	div     WORD [bpbBytesPerSector]        ; sectors used by directory
	xchg    ax, cx
          
	; In the next step we calculate the LBA address (number of the sector)
	; of the root directory and store the location in the AX register
	; AX holds afterwards an LBA address, which must be converted to a CHS address
	;
	; Calcuation: bpbNumberOfFATs * bpbSectorsPerFAT + bpbReservedSectors
	mov     al, BYTE [bpbNumberOfFATs]       ; Number of FATs
	mul     WORD [bpbSectorsPerFAT]          ; Number of sectors used by the FATs
	add     ax, WORD [bpbReservedSectors]    ; Add the boot sector (and reserved sectors, if available)

	; Calculate the address where the first cluster of data begins
	; Calculation: Root Directory Size (register AX) + (size of FATs + boot sector + reserved sectors [register CX])
	mov     WORD [DataSectorBeginning], ax   ; Size of the root directory
    add     WORD [DataSectorBeginning], cx	 ; FAT sectors + boot sector + reserved sectors

	; Convert the calculated LBA address (stored in AX) to a CHS address
	call	LBA2CHS

	; And finally we read the complete root directory into memory
	mov		bx, ROOTDIRECTORY_AND_FAT_OFFSET	; Load the Root Directory at 0x1000
	mov		dh, cl								; Load the number of sectors stored in CX
	call	disk_load							; Perform the I/O operation

	; Now we have to find our file in the Root Directory
	mov     cx, [bpbRootEntries]				; The number of root directory entries
	mov     di, ROOTDIRECTORY_AND_FAT_OFFSET    ; Address of the Root directory
    .Loop:
		push    cx
		mov     cx, 11					; We compare 11 characters (8.3 convention)
		mov     si, KernelName			; Compare against the kernel image name
		push    di
	rep  cmpsb							; Test for string match
		pop     di
		je      LOAD_FAT				; When we have a match, we load the FAT
		pop     cx
		add     di, 32					; When we don't have a match, we go to next root directory entry (+ 32 bytes)
		loop    .Loop
		jmp     FAILURE					; Our kernel image wasn't found in the root directory :-(

LOAD_FAT:
	mov     dx, WORD [di + 0x001A]		; Add 26 bytes to the current entry of the root directory, so that we get the start cluster
	mov     WORD [Cluster], dx          ; Store the 2 bytes of the start cluster (byte 26 & 27 of the root directory entry) in the variable "cluster"

	; Calculate the number of sectors used by all FATs (bpbNumberOfFATs * bpbSectorsPerFAT)
	xor     ax, ax
	mov		BYTE [Track], al			; Initialize the track with 0
	mov		BYTE [Head], al				; Initialize the head with 0
    mov     al, [bpbNumberOfFATs]		; The number of FATs
    mul     WORD [bpbSectorsPerFAT]		; The sectors per FAT
	mov		dh, al						; Store the number of sectors for all FATs in register DX

	; Load the FAT into memory
	mov		bx, ROOTDIRECTORY_AND_FAT_OFFSET		; Offset in memory at which we want to load the FATs
	mov		cx, WORD [bpbReservedSectors]			; Number of the reserved sectors (1)
	add		cx, 1									; Add 1 to the number of reserved sectors, so that our start sector is the 2nd sector (directly after the boot sector)
	mov		BYTE [Sector], cl						; Sector where we start to read
	call	disk_load								; Call the load routine

	mov		bx, KERNEL_OFFSET						; Address where the first cluster should be stored
	push	bx										; Store the current kernel address on the stack

LOAD_IMAGE:
    mov     ax, WORD [Cluster]						; FAT cluster to read
	call    FATCluster2LBA							; Convert the FAT cluster to LBA (result stored in AX)
	
	; Convert the calculated LBA address (input in AX) to a CHS address
	call	LBA2CHS

	xor		dx, dx
	mov     dh, BYTE [bpbSectorsPerCluster]			; Number of the sectors we want to read
	pop		bx										; Get the current kernel address from the stack (for every sector we read, we advance the address by 512 bytes)
	call    disk_load								; Read the cluster into memory
	add		bx, 0x200								; Advance the kernel address by 512 bytes (1 sector that was read from disk)
	push	bx

	; Compute the next cluster that we have to load from disk
	mov     ax, WORD [Cluster]						; identify current cluster
    mov     cx, ax									; copy current cluster
    mov     dx, ax									; copy current cluster
    shr     dx, 0x0001								; divide by two
    add     cx, dx									; sum for (3/2)
    mov     bx, ROOTDIRECTORY_AND_FAT_OFFSET        ; location of FAT in memory
    add     bx, cx									; index into FAT
    mov     dx, WORD [bx]							; read two bytes from FAT
    test    ax, 0x0001
    jnz     .ODD_CLUSTER
          
.EVEN_CLUSTER:
    and     dx, 0000111111111111b					; Take the lowest 12 bits
    jmp     .DONE
         
.ODD_CLUSTER:
	shr     dx, 0x0004								; Take the highest 12 bits
          
.DONE:
    mov     WORD [Cluster], dx						; store new cluster
	cmp     dx, 0x0FF0								; Test for end of file
    jb      LOAD_IMAGE
          
DONE:
	; mov		si, welcome_message
	; mov		ah, 0x0e
	; call	printline

	; Switch to protected mode
	call switch_to_protected_mode
	
	ret

FAILURE:
	mov		ah, 0x0e
	mov		si, KernelError
	call	printline

	ret

;************************************************;
; Convert LBA to CHS
; AX: LBA Address to convert
;
; absolute sector = (logical sector / sectors per track) + 1
; absolute head   = (logical sector / sectors per track) MOD number of heads
; absolute track  = logical sector / (sectors per track * number of heads)
;
;************************************************;
LBA2CHS:
	xor     dx, dx							; prepare dx:ax for operation
	div     WORD [bpbSectorsPerTrack]		; calculate
	inc     dl								; adjust for sector 0
	mov     BYTE [Sector], dl
	xor     dx, dx							; prepare dx:ax for operation
	div     WORD [bpbHeadsPerCylinder]		; calculate
	mov     BYTE [Head], dl
	mov     BYTE [Track], al
	ret

;************************************************;
; Converts a FAT Cluster to LBA.
; We have to substract 2 from the FAT cluster, because the first 2
; FAT clusters have a special purpose, and they have no
; corresponding data cluster in the file
;
; LBA = (FAT Cluster - 2) * sectors per cluster
;************************************************;
FATCluster2LBA:
    sub     ax, 0x0002                          ; zero base cluster number
    xor     cx, cx
    mov     cl, BYTE [bpbSectorsPerCluster]     ; convert byte to word
    mul     cx
    add     ax, WORD [DataSectorBeginning]      ; base data sector
    ret

;=============================================
; Switches the CPU into the x32 Protected Mode
;=============================================
switch_to_protected_mode:
	call EnableA20

	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEGMENT:start_protected_mode
		
;=============================================
; Enables the A20 gate
;=============================================
EnableA20:
	cli					; Disables interrupts
	push	ax			; Save AX on the stack
	mov	al, 0xdd		; Enable the A20 address line on the keyboard controller
	out	0x64, al		; Send the command to the keyboard controller 
	pop	ax				; Restore the value of AX from the stack
	sti					; Enable the interrupts again
	ret 
	
;====================================================
; Here begins the 32 bit code for the Protected Mode
;====================================================
[bits 32]
start_protected_mode:
	; Setup the Data Segment registers
	mov ax, DATA_SEGMENT
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	; Setup the stack
	mov ebp, 0x90000
	mov esp, ebp

	; Print out a character
	; mov al, 'A'
	; mov edx, 0xb8000
	; mov al, 'A'
	; mov ah, 0x0f
	; mov [edx], ax
	; add edx, 2

	; Print out a simple welcome message
	; mov ebx, welcome_message
	; call printstring

	; Jump into the C kernel loaded from the FAT12 file system at 0x1200
	call KERNEL_OFFSET

	jmp $

;================================================
; Prints a null-terminated string
; Input string must be provided in register ebx
;================================================
; printstring:
	; pusha
	; mov edx, 0xb8000

	; printstring_loop:
		; mov al, [ebx]
		; mov ah, 0x0d
		; cmp al, 0
		; je done

		; mov [edx], ax	; Move the current character to the video memory at 0xb8000
		; add ebx, 1	; Move 1 byte forward in the input string
		; add edx, 2	; Move 2 bytes forward in the video memory

		; jmp printstring_loop

	; done:
		; popa
		; ret

; Memory location where our C kernel will be loaded
ROOTDIRECTORY_AND_FAT_OFFSET	equ 0x1000
KERNEL_OFFSET					equ 0x1200

; Number of the sectors that we are reading during the loading of the C kernel
NUMBER_OF_SECTORS_TO_READ equ 0x4

welcome_message:
db 'x', 0

disk_read_error_message:
db 'y', 0

DataSectorBeginning:
dw 0x0000

BOOT_DRIVE:
db 0

Sector			db 0x00
Head			db 0x00
Track			db 0x00
KernelName		db "KERNEL  BIN"
KernelError		db "z", 0
Cluster			dw 0x0000

;=============================================
; Definition of the GDT, needed for the PM
;=============================================
gdt_start:

; Null Descriptor
gdt_null:
dd 0x0
dd 0x0

; Code Segment Descriptor
gdt_code:
dw 0xffff
dw 0x0
db 0x0
db 10011010b
db 11001111b
db 0x0

; Data Segment Descriptor
gdt_data:
dw 0xffff
dw 0x0
db 0x0
db 10010010b
db 11001111b
db 0x0

gdt_end:

;=============================================
; Definition of the GDT Descriptor
;=============================================
gdt_descriptor:
dw gdt_end - gdt_start - 1	; Size of the GDT
dd gdt_start				; Start address of the GDT

CODE_SEGMENT equ gdt_code - gdt_start
DATA_SEGMENT equ gdt_data - gdt_start

; Boot Sector Padding
times 510-($-$$) db 0
dw 0xaa55