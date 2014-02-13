; Tell the Assembler that are loaded at offset 0x7c00
[org 0x7c00]
[bits 16]

; Memory location where our C kernel will be loaded
ROOTDIRECTORY_OFFSET equ 0x1000
KERNEL_OFFSET		 equ 0x1200

; Number of the sectors that we are reading during the loading of the C kernel
NUMBER_OF_SECTORS_TO_READ equ 0x4

jmp start					; Jump over the BPB directly to start of the boot loader	

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

;=============================================
; Switches the CPU into the x32 Protected Mode
;=============================================
switch_to_protected_mode:
	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEGMENT:start_protected_mode

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
	mov al, 'A'
	mov edx, 0xb8000
	mov al, 'A'
	mov ah, 0x0f
	mov [edx], ax
	add edx, 2

	; Print out a simple welcome message
	; mov ebx, welcome_message
	; call printstring

	; Jump into the C kernel loaded from the FAT12 at 0x1000
	;call KERNEL_OFFSET

	jmp $

welcome_message:
db 'Booting...', 0

disk_read_error_message:
db 'Read error!', 0

DataSectorBeginning:
dw 0x0000

BOOT_DRIVE:
db 0

absoluteSector	db 0x00
absoluteHead	db 0x00
absoluteTrack	db 0x00

KernelName		db "KERNEL  BIN"
KernelError		db "Not found", 0
cluster			dw 0x0000

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