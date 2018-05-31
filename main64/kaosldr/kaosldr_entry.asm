[bits 32]
[extern k_main]

; Calls the main function of our C kernel
call k_main
jmp $