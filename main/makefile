# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard drivers/*.c kernel/*.c kernel/pic/*.c kernel/idt/*.c kernel/irq/*.c)
HEADERS = $(wildcard drivers/*.h kernel/*.h kernel/pic/*.h kernel/idt/*.h kernel/irq/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Creates the final OS image
# The boot sector comes before the C kernel image
kaos.img : boot/bootsector.bin kernel/kernel.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -c -s boot/bootsector.bin -f kaos.img
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f kaos.img -i kernel/kernel.bin

# Links the C kernel
kernel/kernel.bin: kernel/kernelentry.o kernel/idt/idt_asm.o kernel/irq/irq_asm.o ${OBJ}
	~/Documents/dev/opt/cross/bin/i586-elf-ld -o $@ -Ttext 0x1200 $^ --oformat binary

# Compiles the C kernel
%.o : %.c ${HEADERS}
	~/Documents/dev/opt/cross/bin/i586-elf-gcc -ffreestanding -c $< -o $@

# Build the kernel entry file
kernel/kernelentry.o : kernel/kernelentry.asm
	~/Documents/dev/nasm-2.13/nasm kernel/kernelentry.asm -f elf -o kernel/kernelentry.o

# Builds the ISR handlers written in Assembler
kernel/idt/idt_asm.o : kernel/idt/idt.asm
	~/Documents/dev/nasm-2.13/nasm kernel/idt/idt.asm -f elf -o kernel/idt/idt_asm.o

# Builds the IRQ handlers written in Assembler
kernel/irq/irq_asm.o : kernel/irq/irq.asm
	~/Documents/dev/nasm-2.13/nasm kernel/irq/irq.asm -f elf -o kernel/irq/irq_asm.o

# Builds the boot sector
boot/bootsector.bin : boot/bootsector.asm
	~/Documents/dev/nasm-2.13/nasm boot/bootsector.asm -f bin -o boot/bootsector.bin
	
# Clean up
clean:
	rm -f boot/*.bin
	rm -f kernel/*.bin kernel/*.o kernel/idt/*.o kernel/pic/*.o kernel/irq/*.o
	rm -f drivers/*.o
	rm -f kaos.img