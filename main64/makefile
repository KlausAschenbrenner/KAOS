# Builds the boot sector
kaos64.img : boot/main.asm
	~/Documents/dev/nasm-2.13/nasm -fbin boot/main.asm -o kaos64.img
	
# Clean up
clean:
	rm -f *.img