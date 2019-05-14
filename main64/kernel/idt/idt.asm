[BITS 64]
[extern IsrHandler]

; Needed that the C code can call the Assembler function "IdtFlush"
[GLOBAL IdtFlush]
[GLOBAL RaiseInterrupt]

; The following macro emits the ISR assembly routine
%macro ISR_NOERRORCODE 1
    [GLOBAL Isr%1]
    Isr%1:
        cli

        ; Produce a new Stack Frame
        push rbp
        mov rbp, rsp

        ; Save the General Purpose Registers on the Stack
        push rdi    ; [rsp + 120]
        push rsi    ; [rsp + 112]
        push rbp    ; [rsp + 104]
        push rsp    ; [rsp + 96]
        push rbx    ; [rsp + 88]
        push rdx    ; [rsp + 80]
        push rcx    ; [rsp + 72]
        push rax    ; [rsp + 64]
        push r8     ; [rsp + 56]
        push r9     ; [rsp + 48]
        push r10    ; [rsp + 40]
        push r11    ; [rsp + 32]
        push r12    ; [rsp + 24]
        push r13    ; [rsp + 16]
        push r14    ; [rsp + 8]
        push r15    ; [rsp + 0]
        
        ; Store the RIP
        mov rax, 0x99000
        mov rbx, [rsp + 136]
        mov [rax], rbx

        ; Store the Error Code
        add rax, 0x8
        mov rbx, 0x0    ; There is no Error Code
        mov [rax], rbx

        ; Store the RDI register
        add rax, 0x8
        mov rbx, [rsp + 120]
        mov [rax], rbx

        ; Store the RSI register
        add rax, 0x8
        mov rbx, [rsp + 112]
        mov [rax], rbx

        ; Store the RBP register
        add rax, 0x8
        mov rbx, [rsp + 104]
        mov [rax], rbx

        ; Store the RSP register
        add rax, 0x8
        mov rbx, [rsp + 96]
        mov [rax], rbx

        ; Store the RBX register
        add rax, 0x8
        mov rbx, [rsp + 88]
        mov [rax], rbx

        ; Store the RDX register
        add rax, 0x8
        mov rbx, [rsp + 80]
        mov [rax], rbx

        ; Store the RCX register
        add rax, 0x8
        mov rbx, [rsp + 72]
        mov [rax], rbx

        ; Store the RAX register
        add rax, 0x8
        mov rbx, [rsp + 64]
        mov [rax], rbx

        ; Store the R8 register
        add rax, 0x8
        mov rbx, [rsp + 56]
        mov [rax], rbx

        ; Store the R9 register
        add rax, 0x8
        mov rbx, [rsp + 48]
        mov [rax], rbx

        ; Store the R10 register
        add rax, 0x8
        mov rbx, [rsp + 40]
        mov [rax], rbx

        ; Store the R11 register
        add rax, 0x8
        mov rbx, [rsp + 32]
        mov [rax], rbx

        ; Store the R12 register
        add rax, 0x8
        mov rbx, [rsp + 24]
        mov [rax], rbx

        ; Store the R13 register
        add rax, 0x8
        mov rbx, [rsp + 16]
        mov [rax], rbx

        ; Store the R14 register
        add rax, 0x8
        mov rbx, [rsp + 8]
        mov [rax], rbx

        ; Store the R15 register
        add rax, 0x8
        mov rbx, [rsp + 0]
        mov [rax], rbx

        ; Call the ISR handler that is implemented in C
        mov rdi, %1          ; 1st parameter
        mov rsi, cr2         ; 2nd parameter
        mov rdx, 0x99000     ; Set the 3rd parameter to the memory location where the structure with the RegisterState is stored
        call IsrHandler

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

        ; Restore the Stack Base Pointer
        pop rbp

        sti
        iretq
%endmacro

; The following macro emits the ISR assembly routine
%macro ISR_ERRORCODE 1
    [GLOBAL Isr%1]
    Isr%1:
        cli

        ; Produce a new Stack Frame
        push rbp
        mov rbp, rsp
        
        ; Save the General Purpose Registers on the Stack
        push rdi    ; [rsp + 120]
        push rsi    ; [rsp + 112]
        push rbp    ; [rsp + 104]
        push rsp    ; [rsp + 96]
        push rbx    ; [rsp + 88]
        push rdx    ; [rsp + 80]
        push rcx    ; [rsp + 72]
        push rax    ; [rsp + 64]
        push r8     ; [rsp + 56]
        push r9     ; [rsp + 48]
        push r10    ; [rsp + 40]
        push r11    ; [rsp + 32]
        push r12    ; [rsp + 24]
        push r13    ; [rsp + 16]
        push r14    ; [rsp + 8]
        push r15    ; [rsp + 0]

        ; RIP where the Exception has occured
        ; We have to add 136 bytes to the Stack Pointer, because we have pushed 16 registers onto the stack previously (16 * 8 bytes + 8 bytes Error Code)
        mov rdx, [rsp + 136]
        
        ; Store the RIP
        mov rax, 0x99000
        mov rbx, [rsp + 144]
        mov [rax], rbx

        ; Store the Error Code
        add rax, 0x8
        mov rbx, [rsp + 128]
        mov [rax], rbx

        ; Store the RDI register
        add rax, 0x8
        mov rbx, [rsp + 120]
        mov [rax], rbx

        ; Store the RSI register
        add rax, 0x8
        mov rbx, [rsp + 112]
        mov [rax], rbx

        ; Store the RBP register
        add rax, 0x8
        mov rbx, [rsp + 104]
        mov [rax], rbx

        ; Store the RSP register
        add rax, 0x8
        mov rbx, [rsp + 96]
        mov [rax], rbx

        ; Store the RBX register
        add rax, 0x8
        mov rbx, [rsp + 88]
        mov [rax], rbx

        ; Store the RDX register
        add rax, 0x8
        mov rbx, [rsp + 80]
        mov [rax], rbx

        ; Store the RCX register
        add rax, 0x8
        mov rbx, [rsp + 72]
        mov [rax], rbx

        ; Store the RAX register
        add rax, 0x8
        mov rbx, [rsp + 64]
        mov [rax], rbx

        ; Store the R8 register
        add rax, 0x8
        mov rbx, [rsp + 56]
        mov [rax], rbx

        ; Store the R9 register
        add rax, 0x8
        mov rbx, [rsp + 48]
        mov [rax], rbx

        ; Store the R10 register
        add rax, 0x8
        mov rbx, [rsp + 40]
        mov [rax], rbx

        ; Store the R11 register
        add rax, 0x8
        mov rbx, [rsp + 32]
        mov [rax], rbx

        ; Store the R12 register
        add rax, 0x8
        mov rbx, [rsp + 24]
        mov [rax], rbx

        ; Store the R13 register
        add rax, 0x8
        mov rbx, [rsp + 16]
        mov [rax], rbx

        ; Store the R14 register
        add rax, 0x8
        mov rbx, [rsp + 8]
        mov [rax], rbx

        ; Store the R15 register
        add rax, 0x8
        mov rbx, [rsp + 0]
        mov [rax], rbx

        ; Call the ISR handler that is implemented in C
        mov rdi, %1          ; 1st parameter
        mov rsi, cr2         ; 2nd parameter
        mov rdx, 0x99000     ; Set the 3rd parameter to the memory location where the structure with the RegisterState is stored
        call IsrHandler

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

        ; Restore the Stack Base Pointer
        pop rbp

        ; Remove the Error Code from the Stack
        add rsp, 8

        ; Return from the ISR routine...
        sti
        iretq
%endmacro

; Emitting our 32 ISR assembly routines
ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE 8
ISR_NOERRORCODE 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_NOERRORCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_NOERRORCODE 21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_NOERRORCODE 30
ISR_NOERRORCODE 31
    
; Loads the IDT table
IdtFlush:
    ; The first function parameter is provided in the RDI register on the x64 architecture
    ; RDI points to the variable _idtPointer (defined in the C code)
    lidt [rdi]
    ret

; Raises some sample interrupts for testing
RaiseInterrupt:
    ; int 0x0
    ; int 0x1
    ; int 0x10
    ; int 0x16
    int 0xE
    ret