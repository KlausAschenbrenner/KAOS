[BITS 64]
[GLOBAL RaiseSysCallAsm]

; Raises a SysCall
RaiseSysCallAsm:
    mov rax, rdi    ; SysCall Number
    mov rbx, rsi    ; SysCall Parameter
    int 0x80
    ret