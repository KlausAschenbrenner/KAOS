[ORG 0x500]
[BITS 16]

Main:
    ; Check whether we support Long Mode or not
    call CheckCPU
    jc NoLongMode

    ; Switch the CPU to x64 Long Mode
    jmp SwitchToLongMode

%include "boot/LongModeDirectly.asm"

[BITS 64]
.LongMode:
    ; Call the x64 Kernel written in C
    call KERNEL_OFFSET

    hlt
    jmp .LongMode

KERNEL_OFFSET                      equ 0x1200

; Pad out the remaining disk sector with zeros
times 512 - ($-$$) db 0