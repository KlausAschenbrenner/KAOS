[BITS 64]
[extern IrqHandler]

; Needed that the C code can call these Assembler functions
[GLOBAL DisableInterrupts]
[GLOBAL EnableInterrupts]

%macro IRQ 2
  global Irq%1
  Irq%1:
        cli

        ; Save the General Purpose Registers on the Stack
        push rdi
        push rsi
        push rbp
        push rsp
        push rbx
        push rdx
        push rcx
        push rax
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15

        ; Call the ISR handler that is implemented in C
        mov rdi, %2
        call IrqHandler

        ; Restore the General Purpose Registers from the Stack
        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rax
        pop rcx
        pop rdx
        pop rbx
        pop rsp
        pop rbp
        pop rsi
        pop rdi

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