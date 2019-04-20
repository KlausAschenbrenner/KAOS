[BITS 64]
[GLOBAL RaiseSysCall]

; Raises a SysCall
RaiseSysCall:
    mov rax, rdi    ; SysCall Number
    mov rbx, rsi    ; SysCall Parameter
    int 0x80
    ret