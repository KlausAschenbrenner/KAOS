# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard *.c syscalls/*.c)
HEADERS = $(wildcard *.h syscalls/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Links the C program
prog2.bin: ${OBJ} syscalls/syscall_asm.o
	~/Documents/dev_x64/opt/cross/bin/x86_64-elf-ld -o $@ -Tlink.ld $^ --oformat binary -z max-page-size=0x1000 -Map prog2.map
	# ~/Documents/dev_x64/opt/cross/bin/x86_64-elf-objdump -S --disassemble main.o > main.asm
	
# Compiles the C program
%.o : %.c ${HEADERS}
	~/Documents/dev_x64/opt/cross/bin/x86_64-elf-gcc -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -c $< -o $@

# Builds the SYSCALL functionality written in Assembler
syscalls/syscall_asm.o : syscalls/syscall.asm
	~/Documents/dev/nasm-2.13/nasm -felf64 syscalls/syscall.asm -o syscalls/syscall_asm.o

# Clean up
clean:
	rm -f *.bin *.o *.asm syscalls/*.o