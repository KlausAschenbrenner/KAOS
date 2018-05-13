[ORG 0x6000]
[BITS 16]

Main:
    ; Check whether we support Long Mode or not
    call CheckCPU
    jc NoLongMode

    call LoadRootDirectory

%include "boot/disk.asm"

; The call to "LoadRootDirectory" continues here...       
DONE:
    ; Switch the CPU to x64 Long Mode
    jmp SwitchToLongMode

FAILURE:
	mov		ah, 0x0e
	mov		si, SecondStageError
    call	printline

	ret

%include "boot/LongModeDirectly.asm"

[BITS 64]
.LongMode:
    ; Call the x64 Kernel written in C
    call IMAGE_OFFSET

    hlt
    jmp .LongMode

ROOTDIRECTORY_AND_FAT_OFFSET	    equ 0x500
IMAGE_OFFSET                        equ 0x1200

Sector			                    db 0x00
Head			                    db 0x00
Track			                    db 0x00
SecondStageName		                db "KERNEL  BIN"
SecondStageError		            db "z", 0
Cluster			                    dw 0x0000

DataSectorBeginning:                dw 0x0000
disk_read_error_message:            db 'y', 0

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