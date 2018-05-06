; Tell the Assembler that are loaded at offset 0x7c00
[ORG 0x7c00]
[BITS 16]

Main:
    ; Setup the ds register
	mov ax, 0
	mov ds, ax

	; Prepare the stack
	mov bp, 0x8000
	mov sp, bp

    ; Enable the A20 Gate
    ; call EnableA20

    ; Loads the 2nd Stage Boot Loader from the 2nd Disk Sector
    mov WORD [MemoryDestination], SECONDSTAGE_BOOTLOADER_OFFSET
    mov BYTE [Sector], 2
    mov BYTE [Track], 0
    mov BYTE [Head], 0
    call LoadDiskSector

    ; 3 -> 18
    mov WORD [MemoryDestination], KERNEL_OFFSET
    mov BYTE [TargetSector], 18
    mov BYTE [Sector], 3
    mov BYTE [Track], 0
    mov BYTE [Head], 0

; Loads in a While-Loop the Kernel from Disk into Memory (while CurrentLoopCounter < LoopTarget)
LoadKernel:
    ; Read the Sector into the current Memory Destination Address
    call LoadDiskSector

    add BYTE [Sector], 1
    add WORD [MemoryDestination], 0x0200

    ; Print out a character when we have read a Disk Sector
	xor	bx, bx
	mov	ah, 0x0e
	mov	al, '.'
    int	0x10

    mov dl, [Sector]
    mov cl, [TargetSector]
    cmp dl, cl                  ; Check if we have reached the end of the loop
    jnz LoadKernel              ; Load the next Sector from Disk - if needed

    ; Jump to the loaded 2nd Stage Boot Loader
    jmp SECONDSTAGE_BOOTLOADER_OFFSET

; Loads a Disk Sector of 512 bytes into Memory
LoadDiskSector:
    mov	ah, 0					; Reset floppy disk function
	mov	dl, 0					; Drive 0 is floppy drive
	int	0x13					; Call BIOS

    ; Read the 2nd sector, where the Second Stage Boot Loader is stored to memory location 0x500
	mov ah, 0x02                ; BIOS read selector function
    mov al, 0x01                ; Number of sectors to be read
    mov ch, BYTE [Track]		; Track
	mov	cl, BYTE [Sector]		; Sector
	mov	dh, BYTE [Head]			; Head

    mov bx, WORD [MemoryDestination]
    mov dl, 0x00                ; Drive Number
    int 0x13					; BIOS interrupt that triggers the I/O

    ; Error handling
    jc DiskError

    ; Check if we have read 1 sector
    mov dh, 1
	cmp	dh, al
	jne	DiskError
ret

DiskError:
	; Print out a character
	xor	bx, bx
	mov	ah, 0x0e
	mov	al, 'F'
	int	0x10
	
    jmp $

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

SECONDSTAGE_BOOTLOADER_OFFSET       equ 0x500
KERNEL_OFFSET                       equ 0x1200

Sector			                    db 0x00
Head			                    db 0x00
Track			                    db 0x00

MemoryDestination                   dw 0x0000
TargetSector                        db 0x00
 
; Pad out the remaining disk sector with zeros
times 510 - ($-$$) db 0
dw 0xAA55