# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard *.c drivers/*.c pic/*.c idt/*.c irq/*.c paging/*.c fat12/*.c heap/*.c Tasks/*.c gdt/*.c syscall/*.c structs/*.c ui/*.c ui/Controls/*.c)
HEADERS = $(wildcard *.h drivers/*.h pic/*.h idt/*.h irq/*.h paging.h fat12/*.h heap/*.h Tasks/*.h gdt/*.h syscall/*.h structs/*.h ui/*.h ui/Controls/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Builds the final Floppy Image
 kaos64.img : bootsector.bin kernel.bin
	fat_imgen -c -s ../boot/bootsector.bin -f ../kaos64.img
	fat_imgen -m -f ../kaos64.img -i ../kaosldr/kaosldr.bin
	fat_imgen -m -f ../kaos64.img -i kernel.bin
	fat_imgen -m -f ../kaos64.img -i ../programs/program1/prog1.bin
	fat_imgen -m -f ../kaos64.img -i ../programs/program2/prog2.bin
	fat_imgen -m -f ../kaos64.img -i ui/Images/close.bmp
	fat_imgen -m -f ../kaos64.img -i ui/Images/logo.bmp
	fat_imgen -m -f ../kaos64.img -i ui/Images/up.bmp
	fat_imgen -m -f ../kaos64.img -i ui/Images/down.bmp
	# ~/Documents/dev_x64/opt/cross/bin/x86_64-elf-objdump -M intel -S --disassemble fat12/fat12.o > fat12/fat12_generated.asm
	# ~/Documents/dev_x64/opt/cross/bin/x86_64-elf-objdump -M intel -S --disassemble gdt/gdt.o > gdt/gdt_output.asm
	# ~/Documents/dev_x64/opt/cross/bin/x86_64-elf-objdump -M intel -S --disassemble Tasks/TaskSwitch.o > Tasks/TaskSwitch_Generated.asm
	# ~/Documents/dev_x64/opt/cross/bin/x86_64-elf-objdump -M intel -S --disassemble ui/window.o > ui/window_generated.asm
	# ~/Documents/dev_x64/opt/cross/bin/x86_64-elf-objdump -M intel -S --disassemble heap/Heap.o > heap/heap_generated.asm
	
# Links the C kernel
kernel.bin: kernel.o idt/idt_asm.o irq/irq_asm.o gdt/gdt_asm.o execute.o Tasks/TaskSwitch.o syscalls/syscall_asm.o syscalls/syscall.o structs/kpcr_asm.o ${OBJ}
	x86_64-elf-ld -o $@ -Tlink.ld $^ --oformat binary -z max-page-size=0x1000 -Map kernel.map

# Compiles the C kernel
%.o : %.c ${HEADERS}
	x86_64-elf-gcc -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -c $< -o $@

# Builds the Task Switch functionality written in Assembler
Tasks/TaskSwitch.o : Tasks/TaskSwitch.asm
	nasm -felf64 Tasks/TaskSwitch.asm -o Tasks/TaskSwitch.o

# Builds the ISR handlers written in Assembler
idt/idt_asm.o : idt/idt.asm
	nasm -felf64 idt/idt.asm -o idt/idt_asm.o

# Builds the GDT functionality written in Assembler
gdt/gdt_asm.o : gdt/gdt.asm
	nasm -felf64 gdt/gdt.asm -o gdt/gdt_asm.o

# Builds the IRQ handlers written in Assembler
irq/irq_asm.o : irq/irq.asm
	nasm -felf64 irq/irq.asm -o irq/irq_asm.o

# Builds the SYSCALL functionality written in Assembler
syscalls/syscall_asm.o : syscalls/syscall.asm
	nasm -felf64 syscalls/syscall.asm -o syscalls/syscall_asm.o

structs/kpcr_asm.o : structs/kpcr.asm
	nasm -felf64 structs/kpcr.asm -o structs/kpcr_asm.o

# Builds the Executor written in Assembler
execute.o : execute.asm
	nasm -felf64 execute.asm -o execute.o

# Builds the Boot Sector
bootsector.bin: ../boot/bootsector.asm
	nasm -fbin ../boot/bootsector.asm -o ../boot/bootsector.bin

# Clean up
clean:
	rm -f ../boot/*.bin
	rm -f *.bin *.map *.o idt/*.o pic/*.o irq/*.o paging/*.o drivers/*.o fat12/*.o heap/*.o Tasks/*.o gdt/*.o syscalls/*.o structs/*.o ui/*.o ui/Controls/*.o
	rm -f ../*.img