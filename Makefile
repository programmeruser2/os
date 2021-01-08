C_SRC = $(wildcard src/*.c)
ASM = $(wildcard src/*.asm)
OBJS = $(patsubst src/%.c,%.o,$(C_SRC)) $(patsubst src/%.asm,%.o,$(ASM))
.PHONY: all test
all: os.iso clean
test: os.iso clean
	qemu-system-i386 -cdrom os.iso
os.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso
kernel.bin: $(OBJS)
	i686-elf-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(OBJS) 
%.o: src/%.asm
	nasm -f elf32 $< -o $@ 
%.o: src/%.c
	i686-elf-gcc -c $^ -nostdlib -ffreestanding -O2 -g # debug symbols 
clean:
	rm *.o
