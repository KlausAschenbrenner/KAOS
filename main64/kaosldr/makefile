# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard drivers/*.c *.c pic/*.c idt/*.c irq/*.c fat12/*.c)
HEADERS = $(wildcard drivers/*.h *.h pic/*.h idt/*.h irq/*.h fat12/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Links the C Loader
kaosldr.bin: kaosldr_entry.o idt/idt_asm.o irq/irq_asm.o EnterLongMode.o ${OBJ}
	~/Documents/dev/opt/cross/bin/i586-elf-ld -o $@ -Tlink.ld $^ --oformat binary -Map kaosldr.map
	
# Compiles the C Loader
%.o : %.c ${HEADERS}
	~/Documents/dev/opt/cross/bin/i586-elf-gcc -ffreestanding -c $< -o $@

# Build the Long Mode Switch file
EnterLongMode.o : EnterLongMode.asm
	~/Documents/dev/nasm-2.13/nasm EnterLongMode.asm -f elf -o EnterLongMode.o

# Build the Loader entry file
kaosldr_entry.o : kaosldr_entry.asm
	~/Documents/dev/nasm-2.13/nasm kaosldr_entry.asm -f elf -o kaosldr_entry.o

# Builds the ISR handlers written in Assembler
idt/idt_asm.o : idt/idt.asm
	~/Documents/dev/nasm-2.13/nasm idt/idt.asm -f elf -o idt/idt_asm.o

# Builds the IRQ handlers written in Assembler
irq/irq_asm.o : irq/irq.asm
	~/Documents/dev/nasm-2.13/nasm irq/irq.asm -f elf -o irq/irq_asm.o

# Clean up
clean:
	rm -f *.bin *.map *.o idt/*.o pic/*.o irq/*.o fat12/*.o
	rm -f drivers/*.o