# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard drivers/*.c kernel/*.c kernel/pic/*.c kernel/idt/*.c kernel/irq/*.c kernel/paging/*.c)
HEADERS = $(wildcard drivers/*.h kernel/*.h kernel/pic/*.h kernel/idt/*.h kernel/irq/*.h kernel/paging.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Builds the final Floppy Image
kaos64.img : bootsector.bin boot.bin kernel/kernel.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -c -s boot/bootsector.bin -f kaos64.img
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f kaos64.img -i boot/boot.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f kaos64.img -i kernel/kernel.bin

# Links the C kernel
kernel/kernel.bin: kernel/kernel.o kernel/idt/idt_asm.o kernel/irq/irq_asm.o ${OBJ}
	~/Documents/dev_x64/opt/cross/bin/x86_64-elf-ld -o $@ -Ttext 0x1200 $^ --oformat binary -z max-page-size=0x1000

# Compiles the C kernel
%.o : %.c ${HEADERS}
	~/Documents/dev_x64/opt/cross/bin/x86_64-elf-gcc -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -c $< -o $@

# Builds the ISR handlers written in Assembler
kernel/idt/idt_asm.o : kernel/idt/idt.asm
	~/Documents/dev/nasm-2.13/nasm -felf64 kernel/idt/idt.asm -o kernel/idt/idt_asm.o

# Builds the IRQ handlers written in Assembler
kernel/irq/irq_asm.o : kernel/irq/irq.asm
	~/Documents/dev/nasm-2.13/nasm -felf64 kernel/irq/irq.asm -o kernel/irq/irq_asm.o

# Builds the Boot Sector
bootsector.bin: boot/bootsector.asm
	~/Documents/dev/nasm-2.13/nasm -fbin boot/bootsector.asm -o boot/bootsector.bin

# Builds the Second Stage Boot Sector
boot.bin: boot/bootsector2.asm
	~/Documents/dev/nasm-2.13/nasm -fbin boot/bootsector2.asm -o boot/boot.bin

# kernel.asm : kernel.o
#	~/Documents/dev_x64/opt/cross/bin/x86_64-elf-objdump -S --disassemble -Mintel idt_asm.o > idt.asm
	
# Clean up
clean:
	rm -f boot/*.bin
	rm -f kernel/*.bin kernel/*.o kernel/idt/*.o kernel/pic/*.o kernel/irq/*.o kernel/paging/*.o
	rm -f drivers/*.o
	rm -f *.img