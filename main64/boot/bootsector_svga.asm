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

    ; Set the graphics mode to 1280 x 1024 - 256 Colors
    ; mov ax, 4F02h
    ; mov bx, 107h
    ; int 0x10

    ; Check the VESA mode
    mov ax, 0x4F01
    mov cx, 0x11A       ; 1280 x 1024 x 64K Colors
    mov di, mode_info_block
    int 0x10

    cmp ax, 0x004F
    jne error

    ; Linear Frame Buffer Address
    ; mov al, [mode_info_block + 40]
    ; call printhexb
    ; mov al, [mode_info_block + 41]
    ; call printhexb
    ; mov al, [mode_info_block + 42]
    ; call printhexb
    ; mov al, [mode_info_block + 43]
    ; call printhexb

    mov al, [mode_info_block + 19]
    call printhexb
    mov al, [mode_info_block + 20]
    call printhexb

    jmp $

printhexb:
    push ax
    shr al, 0x04
    call print_nibble
    pop ax
    and al, 0x0F
    call print_nibble

    ret

print_nibble:
    cmp al, 0x09
    jg .letter
    add al, 0x30
    mov ah, 0x0e
    int 0x10
    ret

.letter:
    add al, 0x37
    mov ah, 0x0e
    int 0x10
    ret

jmp $

error:
    ; Not supported
    mov ah, 0x0e
    mov si, disk_read_error_message
    call printline

    ; jmp $
    hlt

printline:
    mov al, [si]
    cmp al, 0
    je end_printline

    int 0x10
    inc si
    jmp printline

    end_printline:
ret

; 256 bytes long
mode_info_block:
    .attributes     dw
    .window_a       db
    .window_b       db
    .granularity    dw
    .window_size    dw
    .segment_a      dw
    .segment_b      dw
    .win_func_ptr   dd
    .pitch          dw
    .width          dw  ; byte offset 19
    .height         dw  ; byte offset 21
    .w_char         db
    .y_char         db
    .planes         db
    .bpp            db
    .banks          db
    .memory_model   db
    .bank_size      db
    .image_pages    db
    .reserved0      db
    .red_mask       db
    .red_position   db
    .green_mask     db
    .green_position db
    .blue_mask      db
    .blue_position  db
    .reserved_mask  db
    .reserved_pos   db
    .direct_col_att db
    .frame_buffer   dd  ; byte offset 40
    .mem_off        dd
    .mem_size       dw  ; byte offset 48
    times 206       db

disk_read_error_message:            db 'd', 0

; Pad out the remaining disk sector with zeros
times 510 - ($-$$) db 0
dw 0xAA55