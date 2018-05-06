[BITS 64]
[extern IrqHandler]

; Needed that the C code can call these Assembler functions
[GLOBAL DisableInterrupts]
[GLOBAL EnableInterrupts]

%macro IRQ 2
  global Irq%1
  Irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
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

; This is our common IRQ stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame. 
irq_common_stub:
    ; Push all general purpose Registers onto the stack
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push rax                 ; save the data segment descriptor

    mov ax, 0x10             ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call IrqHandler

    pop rbx                  ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    ; Pop all general purpose Registers from the stack
    pop rdi    
    pop rsi    
    pop rbp    
    pop rbx    
    pop rdx    
    pop rcx
    pop rax

   add esp, 8               ; Cleans up the pushed error code and pushed ISR number
   sti
   iret

; Disables the hardware interrupts
DisableInterrupts:
    cli
    ret

; Enables the hardware interrupts
EnableInterrupts:
    sti
    ret