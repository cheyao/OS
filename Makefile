C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}
# -g: Use debugging symbols in gcc
CFLAGS = -g

all: run 
	-rm -rf *.bin *.dis *.o *.elf
	-rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > output/os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ 

run: clean os-image.bin
	qemu-system-x86_64 -fda output/os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: clean os-image.bin kernel.elf
	qemu-system-x86_64 -s -S -fda output/os-image.bin &
	x86_64-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	x86_64-elf-gcc ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf64 -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	-rm -rf *.bin *.dis *.o os-image.bin *.elf
	-rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o