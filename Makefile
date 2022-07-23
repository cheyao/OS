C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/int.o}
# -g: Use debugging symbols in gcc
CFLAGS = -g3 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
                  		 -Wall -Wextra -Werror -I /Users/ray/OS

.PHONY: clean all run debug

all: run

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin # Don't mind
	cat $^ > output/os-image.bin # Don't mind

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ} # Don't mind
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary # Don't mind

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ} # Don't mind
	i686-elf-ld -o $@ -Ttext 0x1000 $^ # Don't mind

run: boot/bootsect.bin
	qemu-system-x86_64 -fda boot/bootsect.bin -no-reboot -D ./log.txt -d int

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-x86_64 -s -S -fda output/os-image.bin -no-reboot &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	-rm -rf *.bin *.dis *.o os-image.bin *.elf
	-rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o  drivers/*.o cpu/*.o cpu/*.bin


# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS} # Don't mind
	i686-elf-gcc ${CFLAGS} -ffreestanding -c $< -o $@ # Don't mind

%.o: %.asm # Don't mind
	nasm $< -f elf32 -o $@ # Don't mind

%.bin: %.asm
	nasm $< -f bin -o $@
