# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard drivers/*.c kernel/*.c kernel/pic/*.c kernel/idt/*.c kernel/irq/*.c kernel/fat12/*.c)
HEADERS = $(wildcard drivers/*.h kernel/*.h kernel/pic/*.h kernel/idt/*.h kernel/irq/*.h kernel/fat12/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Creates the final OS image
# The boot sector comes before the C kernel image
kaos.img : boot/bootsector.bin kernel/kernel.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -c -s boot/bootsector.bin -f kaos.img
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f kaos.img -i kernel/kernel.bin
	cp kernel/kernel.bin ../main64/loader.bin
	# ~/Documents/dev/opt/cross/bin/i586-elf-objdump -S --disassemble -Mintel drivers/floppy.o > drivers/floppy_generated.asm

# Links the C kernel
kernel/kernel.bin: kernel/kernelentry.o kernel/idt/idt_asm.o kernel/irq/irq_asm.o kernel/EnterLongMode.o ${OBJ}
	~/Documents/dev/opt/cross/bin/i586-elf-ld -o $@ -Ttext 0x20000 $^ --oformat binary -Map kernel.map

# Compiles the C kernel
%.o : %.c ${HEADERS}
	~/Documents/dev/opt/cross/bin/i586-elf-gcc -ffreestanding -c $< -o $@

# Build the Long Mode Switch file
kernel/EnterLongMode.o : kernel/EnterLongMode.asm
	~/Documents/dev/nasm-2.13/nasm kernel/EnterLongMode.asm -f elf -o kernel/EnterLongMode.o

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
	rm -f kernel/*.bin kernel/*.o kernel/idt/*.o kernel/pic/*.o kernel/irq/*.o kernel/fat12/*.o
	rm -f drivers/*.o
	rm -f kaos.img