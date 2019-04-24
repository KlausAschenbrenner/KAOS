; Tell the Assembler that are loaded at offset 0x7c00
[ORG 0x7c00]
[BITS 16]

jmp Main					; Jump over the BPB directly to start of the boot loader
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

Main:
    ; Setup the ds register
	xor ax, ax
	mov ds, ax
	mov es, ax

	; Prepare the stack
	mov ax, 0x7000
	mov ss, ax
	mov bp, 0x8000
	mov sp, bp

	; Set the graphics mode to VGA
	; mov ah, 00h
	; mov al, 13h
	; int 0x10

	call EnableA20
    call LoadRootDirectory

%include "../boot/disk.asm"
          
DONE:
	; Switch to protected mode
	call switch_to_protected_mode
	
	ret

FAILURE:
	mov		ah, 0x0e
	mov		si, SecondStageError
	call	printline

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

;=============================================
; Enables the A20 gate
;=============================================
EnableA20:
	cli					; Disables interrupts
	push	ax			; Save AX on the stack
	mov	al, 0xdd		; Enable the A20 address line on the keyboard controller
	out	0x64, al		; Send the command to the keyboard controller 
	; mov al, 2
	; out 0x92, al
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
	mov ebp, 0x70000
	mov esp, ebp

	; Executes KAOSLDR.BIN loaded from the FAT12 file system at 0x20000
	call LOADER_OFFSET

    jmp $

ROOTDIRECTORY_AND_FAT_OFFSET	    equ 0x500
IMAGE_OFFSET                        equ 0x0
LOADER_OFFSET						equ 0x20000

Sector			                    db 0x00
Head			                    db 0x00
Track			                    db 0x00
SecondStageName		                db "KAOSLDR BIN"
SecondStageError		            db '', 0
Cluster			                    dw 0x0000

welcome_message:                    db '', 0
disk_read_error_message:            db 'e', 0
DataSectorBeginning:                dw 0x0000

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

; Pad out the remaining disk sector with zeros
times 510 - ($-$$) db 0
dw 0xAA55