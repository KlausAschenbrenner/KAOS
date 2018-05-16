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
	mov ax, 0
	mov ds, ax

	; Prepare the stack
	mov bp, 0x8000
	mov sp, bp

	call EnableA20
    call LoadRootDirectory

%include "boot/disk.asm"
          
DONE:
    ; Execute the 2nd Stage Boot Loader
    jmp IMAGE_OFFSET
	
	ret

FAILURE:
	mov		ah, 0x0e
	mov		si, SecondStageError
	call	printline

	ret

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

ROOTDIRECTORY_AND_FAT_OFFSET	    equ 0x500
IMAGE_OFFSET                        equ 0x6000

Sector			                    db 0x00
Head			                    db 0x00
Track			                    db 0x00
SecondStageName		                db "BOOT    BIN"
SecondStageError		            db "z", 0
Cluster			                    dw 0x0000

welcome_message:                    db 'x', 0
disk_read_error_message:            db 'y', 0
DataSectorBeginning:                dw 0x0000

; Pad out the remaining disk sector with zeros
times 510 - ($-$$) db 0
dw 0xAA55