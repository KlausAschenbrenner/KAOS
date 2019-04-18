[GLOBAL GdtFlush]

; Loads the GDT table
GdtFlush:
    cli

    ; The first function parameter is provided in the RDI register on the x64 architecture
    ; RDI points to the variable _gdtPointer (defined in the C code)
    lgdt [rdi]

    ; Load the TSS
    mov ax, 0x28
    ; ltr ax

    sti
    ret