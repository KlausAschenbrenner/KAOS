[BITS 64]
[GLOBAL TaskSwitch]
[extern MoveToNextTask]

; Defines the various offsets into the C structure "Task"
%define TaskState_RAX       0
%define TaskState_RBX       8
%define TaskState_RCX       16
%define TaskState_RDX       24 
%define TaskState_RBP       32
%define TaskState_RSI       48
%define TaskState_R8        64
%define TaskState_R9        72
%define TaskState_R10       80
%define TaskState_R11       88
%define TaskState_R12       96
%define TaskState_R13       104
%define TaskState_R14       112
%define TaskState_R15       120
%define TaskState_CR3       128

%define TaskState_RDI       136
%define TaskState_RIP       144
%define TaskState_CS        152
%define TaskState_RFLAGS    160
%define TaskState_RSP       168
%define TaskState_SS        176

TaskSwitch:
    ; RDI stores a pointer to the current Task
    ; It is passed in as the 1st parameter when we call the
    ; Assembler function "TaskSwich" in the C Code

    ; Save the current Task State
    mov [rdi + TaskState_RAX], rax
    mov [rdi + TaskState_RBX], rbx
    mov [rdi + TaskState_RCX], rcx
    mov [rdi + TaskState_RDX], rdx
    mov [rdi + TaskState_RBP], rbp
    mov [rdi + TaskState_RSI], rsi
    mov [rdi + TaskState_R8],  r8
    mov [rdi + TaskState_R9],  r9
    mov [rdi + TaskState_R10], r10
    mov [rdi + TaskState_R11], r11
    mov [rdi + TaskState_R12], r12
    mov [rdi + TaskState_R13], r13
    mov [rdi + TaskState_R14], r14
    mov [rdi + TaskState_R15], r15

    ; TODO
    ; mov rax, cr3
    ; mov [rdi + TaskState_CR3], rax

    pop rax
    ; mov [rdi + TaskState_RDI], rax
    ; pop rax
    ; mov [rdi + TaskState_RIP], rax
    ; pop rax
    ; mov [rdi + TaskState_CS], rax
    ; pop rax
    ; mov [rdi + TaskState_RFLAGS], rax
    ; pop rax
    ; mov [rdi + TaskState_RSP], rax
    ; pop rax
    ; mov [rdi + TaskState_SS], rax

    ; Move the head Task of the RUNNABLE queue to the tail
    call MoveToNextTask

    ; RSI stores a pointer to the next Task
    ; It is passed in as the 2nd parameter when we call the
    ; Assembler function "TaskSwitch" in the C Code

    ; mov rdi, rsi
    ; mov rax, [rdi + TaskState_SS]
    ; push rax
    ; mov rax, [rdi + TaskState_RSP]
    ; push rax
    ; mov rax, [rdi + TaskState_RFLAGS]
    ; push rax
    ; mov rax, [rdi + TaskState_CS]
    ; push rax
    ; mov rax, [rdi + TaskState_RIP]
    ; push rax
    ; mov rax, [rdi + TaskState_RDI]
    ; push rax

    ; push qword [rdi + TaskState_RDI]

    mov rax, [rdi + TaskState_RAX]
    mov rbx, [rsi + TaskState_RBX]
    mov rcx, [rsi + TaskState_RCX]
    mov rdx, [rsi + TaskState_RDX]
    ; mov rbp, [rsi + TaskState_RBP]
    ; mov rsi, [rsi + TaskState_RSI]
    mov r8, [rsi + TaskState_R8]
    mov r9, [rsi + TaskState_R9]
    mov r10, [rsi + TaskState_R10]
    mov r11, [rsi + TaskState_R11]
    mov r12, [rsi + TaskState_R12]
    mov r13, [rsi + TaskState_R13]
    mov r14, [rsi + TaskState_R14]
    mov r15, [rsi + TaskState_R15]

    ; pop rdi

    ; TODO
    ; mov rax, [rsi + TaskState_CR3]
    ; mov cr3, rax

    ret