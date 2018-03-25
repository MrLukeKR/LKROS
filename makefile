all: remove kernelObject kernelBin bootloaderBin concat osimageBin osIso emulate

remove: 
	rm -f osimage.bin 

kernelObject: kernel.c
	gcc -ffreestanding -c kernel.c -o kernel.o -m32 

kernelBin: kernel.o
	ld -o kernel.bin -Ttext 0x7e00 kernel.o -m elf_i386 --oformat binary 

bootloaderBin: bootloader.asm data.asm functions.asm gdt.asm protectedfunctions.asm switch.asm
	nasm bootloader.asm -f bin -o bootloader.bin

concat: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > osimage.bin


osimageBin:
	truncate osimage.bin -s 1474560

osIso: osimage.bin
	mkisofs -o os.iso -V MyOS -b osimage.bin ~/Documents/MyOS

emulate: osimage.bin
	qemu-system-x86_64 -m 2G osimage.bin
