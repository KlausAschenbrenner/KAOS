[BITS 64]
[GLOBAL MoveKPCRToRegister]
[GLOBAL GetKPCR]

MoveKPCRToRegister:
    mov r14, rdi
    ret

GetKPCR
    mov rax, r14
    ret