# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard *.c drivers/*.c pic/*.c idt/*.c irq/*.c paging/*.c fat12/*.c heap/*.c Tasks/*.c)
HEADERS = $(wildcard *.h drivers/*.h pic/*.h idt/*.h irq/*.h paging.h fat12/*.h heap/*.h Tasks/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Builds the final Floppy Image
kaos64.img : bootsector.bin kernel.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -c -s ../boot/bootsector.bin -f ../kaos64.img
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f ../kaos64.img -i ../kaosldr/kaosldr.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f ../kaos64.img -i kernel.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f ../kaos64.img -i ../programs/program1/prog1.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f ../kaos64.img -i ../programs/program2/prog2.bin
	
# Links the C kernel
kernel.bin: kernel.o idt/idt_asm.o irq/irq_asm.o execute.o Tasks/TaskSwitch.o ${OBJ}
	~/Documents/dev_x64/opt/cross/bin/x86_64-elf-ld -o $@ -Tlink.ld $^ --oformat binary -z max-page-size=0x1000 -Map kernel.map

# Compiles the C kernel
%.o : %.c ${HEADERS}
	~/Documents/dev_x64/opt/cross/bin/x86_64-elf-gcc -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -c $< -o $@

# Builds the Task Switch functionality written in Assembler
Tasks/TaskSwitch.o : Tasks/TaskSwitch.asm
	~/Documents/dev/nasm-2.13/nasm -felf64 Tasks/TaskSwitch.asm -o Tasks/TaskSwitch.o

# Builds the ISR handlers written in Assembler
idt/idt_asm.o : idt/idt.asm
	~/Documents/dev/nasm-2.13/nasm -felf64 idt/idt.asm -o idt/idt_asm.o

# Builds the IRQ handlers written in Assembler
irq/irq_asm.o : irq/irq.asm
	~/Documents/dev/nasm-2.13/nasm -felf64 irq/irq.asm -o irq/irq_asm.o

# Builds the Executor written in Assembler
execute.o : execute.asm
	~/Documents/dev/nasm-2.13/nasm -felf64 execute.asm -o execute.o

# Builds the Boot Sector
bootsector.bin: ../boot/bootsector.asm
	~/Documents/dev/nasm-2.13/nasm -fbin ../boot/bootsector.asm -o ../boot/bootsector.bin

# Clean up
clean:
	rm -f ../boot/*.bin
	rm -f *.bin *.map *.o idt/*.o pic/*.o irq/*.o paging/*.o drivers/*.o fat12/*.o heap/*.o
	rm -f ../*.img