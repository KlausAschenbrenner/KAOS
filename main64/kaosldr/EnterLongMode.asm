%define PAGE_PRESENT    (1 << 0)
%define PAGE_WRITE      (1 << 1)
 
%define CODE_SEG     0x0008
%define DATA_SEG     0x0010

[GLOBAL SwitchToLongMode]
 
ALIGN 4
IDT:
    .Length       dw 0
    .Base         dd 0
 
; Function to switch directly to long mode from real mode.
; Identity maps the first 4MiB.
 
; es:edi    Should point to a valid page-aligned 16KiB buffer, for the PML4, PDPT, PD and a PT.
; ss:esp    Should point to memory that can be used as a small (1 uint32_t) stack
 

; =========================================
; Memory Layout of the various Page Tables
; =========================================
; [Page Map Level 4 at 0x8000]
; Entry 001: 0x09000 (es:di + 0x1000)
; Entry ...
; Entry 256: 0x13000 (es:di + 0x5000)   => Needed for the Higher Half Mapping of the Kernel
; Entry ...
; Entry 512

; [Page Directory Pointer Table at 0x09000]
; Entry 001: 0x10000 (es:di + 0x2000)
; Entry ...
; Entry 512

; [Page Directory Table at 0x10000]
; Entry 001: 0x11000 (es:di + 0x3000)
; Entry 002: 0x12000 (es:di + 0x4000)
; Entry ...
; Entry 512

; [Page Table 1 at 0x11000]
; Entry 001: 0x000000
; Entry ...
; Entry 512: 0x1FF000

; [Page Table 2 at 0x12000]
; Entry 001: 0x200000
; Entry ...
; Entry 512: 0x2FF000

; ==========================================================================
; The following tables are needed for the Higher Half Mapping of the Kernel
; ==========================================================================
; [Page Directory Pointer Table at 0x13000]
; Entry 001: 0x14000 (es:di + 0x6000)
; Entry ...
; Entry 512

; [Page Directory Table at 0x14000]
; Entry 001: 0x15000 (es:di + 0x7000)
; Entry ...
; Entry 512

; [Page Table 1 at 0x15000]
; Entry 001: 0x000000
; Entry 002: 0x001000
; Entry 003: 0x002000
; Entry ...
; Entry 512: 0x200000

SwitchToLongMode:
    mov edi, 0x8000
    
    ; Zero out the 16KiB buffer.
    ; Since we are doing a rep stosd, count should be bytes/4.   
    push di                           ; REP STOSD alters DI.
    mov ecx, 0x1000
    xor eax, eax
    cld
    rep stosd
    pop di                            ; Get DI back.
 
    ; Build the Page Map Level 4 (PML4)
    ; es:di points to the Page Map Level 4 table.
    lea eax, [es:di + 0x1000]               ; Put the address of the Page Directory Pointer Table in to EAX.
    or eax, PAGE_PRESENT | PAGE_WRITE       ; Or EAX with the flags - present flag, writable flag.
    mov [es:di], eax                        ; Store the value of EAX as the first PML4E.

    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================
    ; Add the 256th entry to the PML4...
    lea eax, [es:di + 0x5000]
    or eax, PAGE_PRESENT | PAGE_WRITE
    mov [es:di + 0x800], eax                ; 256th entry * 8 bytes per entry

    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================
 
    ; Build the Page Directory Pointer Table (PDP)
    lea eax, [es:di + 0x2000]               ; Put the address of the Page Directory in to EAX.
    or eax, PAGE_PRESENT | PAGE_WRITE       ; Or EAX with the flags - present flag, writable flag.
    mov [es:di + 0x1000], eax               ; Store the value of EAX as the first PDPTE.

    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================
    ; Build the Page Directory Pointer Table (PDP)
    lea eax, [es:di + 0x6000]               ; Put the address of the Page Directory in to EAX.
    or eax, PAGE_PRESENT | PAGE_WRITE       ; Or EAX with the flags - present flag, writable flag.
    mov [es:di + 0x5000], eax               ; Store the value of EAX as the first PDPTE.
    
    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================
 
    ; Build the Page Directory (PD Entry 1)
    lea eax, [es:di + 0x3000]               ; Put the address of the Page Table in to EAX.
    or eax, PAGE_PRESENT | PAGE_WRITE       ; Or EAX with the flags - present flag, writeable flag.
    mov [es:di + 0x2000], eax               ; Store to value of EAX as the first PDE.

    ; Build the Page Directory (PD Entry 2)
    lea eax, [es:di + 0x4000]               ; Put the address of the Page Table in to EAX.
    or eax, PAGE_PRESENT | PAGE_WRITE       ; Or EAX with the flags - present flag, writeable flag.
    mov [es:di + 0x2008], eax               ; Store to value of EAX as the second PDE.

    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================
    ; Build the Page Directory (PD Entry 1)
    lea eax, [es:di + 0x7000]               ; Put the address of the Page Table in to EAX.
    or eax, PAGE_PRESENT | PAGE_WRITE       ; Or EAX with the flags - present flag, writeable flag.
    mov [es:di + 0x6000], eax               ; Store to value of EAX as the first PDE.

    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================
 
    push di                                 ; Save DI for the time being.
    lea di, [di + 0x3000]                   ; Point DI to the page table.
    mov eax, PAGE_PRESENT | PAGE_WRITE      ; Move the flags into EAX - and point it to 0x0000.
    
    ; Build the Page Table (PT 1)
.LoopPageTable:
    mov [es:di], eax
    add eax, 0x1000
    add di, 8
    cmp eax, 0x200000                 ; If we did all 4MiB, end.
    jb .LoopPageTable

    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================

    pop di
    push di

    lea di, [di + 0x7000]                   ; Load the address of the 1st Page Table for the Higher Half Mapping of the Kernel
    mov eax, PAGE_PRESENT | PAGE_WRITE      ; Move the flags into EAX - and point it to 0x0000.
    
    ; Build the Page Table (PT 1)
 .LoopPageTableHigherHalf:
    mov [es:di], eax
    add eax, 0x1000
    add di, 8
    cmp eax, 0x200000            ; If we did all 2MiB, end.
    jb .LoopPageTableHigherHalf

    ; =================================================
    ; Needed for the Higher Half Mapping of the Kernel
    ; =================================================
 
    pop di                            ; Restore DI.

    ; Disable IRQs
    mov al, 0xFF                      ; Out 0xFF to 0xA1 and 0x21 to disable all IRQs.
    out 0xA1, al
    out 0x21, al
 
    nop
    nop
 
    lidt [IDT]                        ; Load a zero length IDT so that any NMI causes a triple fault.
 
    ; Enter long mode.
    mov eax, 10100000b                ; Set the PAE and PGE bit.
    mov cr4, eax
 
    mov edx, edi                      ; Point CR3 at the PML4.
    mov cr3, edx
 
    mov ecx, 0xC0000080               ; Read from the EFER MSR. 
    rdmsr    
 
    or eax, 0x00000100                ; Set the LME bit.
    wrmsr
 
    mov ebx, cr0                      ; Activate long mode -
    or ebx, 0x80000001                 ; - by enabling paging and protection simultaneously.
    mov cr0, ebx                    
 
    lgdt [GDT.Pointer]                ; Load GDT.Pointer defined below.
 
    jmp CODE_SEG:LongMode             ; Load CS with 64 bit segment and flush the instruction cache

CheckCPU:
    ; Check whether CPUID is supported or not.
    pushfd                            ; Get flags in EAX register.
 
    pop eax
    mov ecx, eax  
    xor eax, 0x200000 
    push eax 
    popfd
 
    pushfd 
    pop eax
    xor eax, ecx
    shr eax, 21 
    and eax, 1                        ; Check whether bit 21 is set or not. If EAX now contains 0, CPUID isn't supported.
    push ecx
    popfd 
 
    test eax, eax
    jz NoLongMode
 
    mov eax, 0x80000000   
    cpuid                 
 
    cmp eax, 0x80000001               ; Check whether extended function 0x80000001 is available are not.
    jb NoLongMode                    ; If not, long mode not supported.
 
    mov eax, 0x80000001  
    cpuid                 
    test edx, 1 << 29                 ; Test if the LM-bit, is set or not.
    jz NoLongMode                    ; If not Long mode not supported.
 
    ret
 
NoLongMode:
    ; Print out a character
    xor	bx, bx
    mov	ah, 0x0e
    mov	al, 'E'
    int	0x10
   
    jmp $
 
    ; Global Descriptor Table
GDT:
.Null:
    dq 0x0000000000000000             ; Null Descriptor - should be present.
 
.Code:
    ; 00000000 00100000 10011010 00000000
    ; 00000000 00000000 00000000 00000000
    dq 0x00209A0000000000             ; 64-bit Kernel Mode (Ring 0) Code Descriptor (exec/read)

    ; 00000000 00000000 10010010 00000000
    ; 00000000 00000000 00000000 00000000
    dq 0x0000920000000000             ; 64-bit Kernel Mode (Ring 0) Data Descriptor (read/write)
ALIGN 4
    dw 0                              ; Padding to make the "address of the GDT" field aligned on a 4-byte boundary
 
.Pointer:
    dw $ - GDT - 1                    ; 16-bit Size (Limit) of GDT.
    dd GDT                            ; 32-bit Base Address of GDT. (CPU will zero extend to 64-bit)
 
[BITS 64]      
LongMode:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Setup the stack
	mov rax, qword 0xFFFF800000050000
    mov rsp, rax
    mov rbp, rsp

    ; Set the inital RBP to NULL, so that we can produce a Stack Trace in the Exception Handler
    xor rbp, rbp

    ; Execute the 64-bit Kernel, which is stored at 0xFFFF800000110000
    mov r15, qword 0xFFFF800000110000
    mov rax, qword 0xFFFF800000110000
    call rax