[BITS 64]
[GLOBAL SysCallHandlerAsm]
[EXTERN SysCallHandlerC]
[EXTERN printf_long]

SysCallHandlerAsm:
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
    mov rdi, rax
    mov rsi, rbx
    call SysCallHandlerC

    ; Restore the General Purpose Registers from the Stack
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    
    ; We don't restore the RAX register, because it contains the result of the SysCall (from the function call to "SysCallHandlerC").
    ; So we just pop the old RAX value into RCX and then pop the old RCX value into RCX
    ; pop rax
    pop rcx
    pop rcx
    
    pop rdx
    pop rbx
    pop rsp
    pop rbp
    pop rsi
    pop rdi

    sti
    iretq