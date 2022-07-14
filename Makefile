C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/int.o}
# -g: Use debugging symbols in gcc
CFLAGS = -g3 -Wall -Wextra -pedantic

.PHONY: clean all run debug

all: run

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

run: os-image.bin
	qemu-system-x86_64 -fda output/os-image.bin -no-reboot -D ./log.txt -d int

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-x86_64 -s -S -fda output/os-image.bin -no-reboot &
	x86_64-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	-rm -rf *.bin *.dis *.o os-image.bin *.elf
	-rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o  drivers/*.o cpu/*.o cpu/*.bin


# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	x86_64-elf-gcc ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf64 -o $@

boot/kernel_entry.o: boot/kernel_entry.asm
	nasm boot/kernel_entry.asm -f elf64 -o boot/kernel_entry.o

%.bin: %.asm
	nasm $< -f bin -o $@
