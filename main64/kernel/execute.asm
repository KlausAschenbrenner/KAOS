[BITS 64]
[GLOBAL ExecuteProgram]

; Executes the loaded program
ExecuteProgram:
    mov rax, qword 0xFFFF8000FFFF0000
    jmp rax

    ; Prints out "OK"
    ; mov rax, 0x2f592f412f4b2f4f
    ; mov qword [0xb8000], rax 

    ret