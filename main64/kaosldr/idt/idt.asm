[bits 32]
[extern IsrHandler]

; Needed that the C code can call the Assembler function "IdtFlush"
[GLOBAL IdtFlush]
[GLOBAL RaiseInterrupt]

; The following macro emits the ISR assembly routine
%macro ISR_NOERRORCODE 1
    [GLOBAL Isr%1]
    Isr%1:
        cli
        push byte 0
        push byte %1
        jmp IsrCommonStub
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
ISR_NOERRORCODE 8
ISR_NOERRORCODE 9
ISR_NOERRORCODE 10
ISR_NOERRORCODE 11
ISR_NOERRORCODE 12
ISR_NOERRORCODE 13
ISR_NOERRORCODE 14
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

; Common function for ISR handling
IsrCommonStub:
    pusha
    mov ax, ds
    push eax
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Call the ISR handler that is implemented in C
    call IsrHandler
    
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa
    add esp, 8
    sti
    iret
    
; Loads the IDT table
IdtFlush:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; Raises some sample interrupts for testing
RaiseInterrupt:
    int 0x0
    int 0x1
    int 0x10
    int 0x16
    ret