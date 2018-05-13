[BITS 64]
[extern IrqHandler]

; Needed that the C code can call these Assembler functions
[GLOBAL DisableInterrupts]
[GLOBAL EnableInterrupts]

%macro IRQ 2
  global Irq%1
  Irq%1:
        cli

        ; Call the ISR handler that is implemented in C
        mov rdi, %2
        call IrqHandler

        sti
        iretq
%endmacro

IRQ 0,  32
IRQ 1,  33
IRQ 2,  34
IRQ 3,  35
IRQ 4,  36
IRQ 5,  37
IRQ 6,  38
IRQ 7,  39
IRQ 8,  40
IRQ 9,  41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 36
IRQ 15, 47

; Disables the hardware interrupts
DisableInterrupts:
    cli
    ret

; Enables the hardware interrupts
EnableInterrupts:
    sti
    ret