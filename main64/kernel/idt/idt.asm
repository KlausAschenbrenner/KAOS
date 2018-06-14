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
        mov rdi, %1
        mov rsi, cr2
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

        sti
        iretq
%endmacro

; The following macro emits the ISR assembly routine
%macro ISR_ERRORCODE 1
    [GLOBAL Isr%1]
    Isr%1:
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

        ; Call the ISR Handler that is implemented in C
        mov rdi, %1         ; ISR Number
        mov rsi, cr2        ; Virtual Address where the Page Fault has occured
        call IsrHandler     ; ISR Handler

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

        ; Remove the Error Code from the Stack
        add rsp, 8

        ; Return from the ISR routine...
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