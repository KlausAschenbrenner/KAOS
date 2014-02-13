# Old Version!
# kaos.bin : boot/bootsector.bin kernel/kernel.bin
#	cat boot/bootsector.bin kernel/kernel.bin > kaos.bin
#	cp kaos.bin ../kaos.bin


# Creates the final OS image
# The boot sector comes before the C kernel image
kaos.img : boot/bootsector.bin kernel/kernel.bin
	~/Documents/dev/opt/cross/bin/fat_imgen -c -s boot/bootsector.bin -f kaos.img
	~/Documents/dev/opt/cross/bin/fat_imgen -m -f kaos.img -i kernel/kernel.bin
	# miso kaos.iso -ab kaos.img
	# cp kaos.img ../kaos.img
	# cp kaos.iso ../kaos.iso
	# cp ../kaos.iso /cygdrive/z/Klaus/Documents/kaos.iso

# Links the C kernel
kernel/kernel.bin: kernel/kernelentry.o kernel/kernel.o drivers/common.o drivers/screen.o
	~/Documents/dev/opt/cross/bin/i586-elf-ld -o kernel/kernel.bin -Ttext 0x1200 kernel/kernelentry.o kernel/kernel.o drivers/common.o drivers/screen.o --oformat binary

# Compiles the C kernel entry file
kernel/kernel.o : kernel/kernel.c drivers/screen.c drivers/common.c
	~/Documents/dev/opt/cross/bin/i586-elf-gcc -ffreestanding -c kernel/kernel.c -o kernel/kernel.o
	~/Documents/dev/opt/cross/bin/i586-elf-gcc -ffreestanding -c drivers/common.c -o drivers/common.o
	~/Documents/dev/opt/cross/bin/i586-elf-gcc -ffreestanding -c drivers/screen.c -o drivers/screen.o

# Build the kernel entry file
kernel/kernelentry.o : kernel/kernelentry.asm
	nasm kernel/kernelentry.asm -f elf -o kernel/kernelentry.o

# Build the boot sector
boot/bootsector.bin : boot/bootsector.asm
	nasm boot/bootsector.asm -f bin -o boot/bootsector.bin
	
# Clean up
clean:
	rm boot/*.bin
	rm kernel/*.bin kernel/*.o
	rm drivers/*.o
	rm kaos.img
	# rm kaos.iso