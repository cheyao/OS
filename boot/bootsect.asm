; Identical to lesson 13's boot sector, but the %included files have new paths
[org 0x7c00]
KERNEL_OFFSET equ 0x00007E00 ; The same one we used when linking the kernel
PAGING_OFFSET equ 0x00001000

    mov [BOOT_DRIVE], dl ; Remember that the BIOS sets us the boot drive in 'dl' on boot
    mov bp, 0x7BFF
    mov sp, bp

    mov ah, 0x01                    ; Remove cursor
    mov ch, 0x3F
    int 0x10
    call load_kernel ; read the kernel from disk


    call switch_to_pm ; disable interrupts, load GDT,  etc. Finally jumps to 'BEGIN_PM'
    jmp $ ; Never executed

load_kernel:
    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 16 ; Our future kernel will be larger, make this big
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/switch_pm.asm"
%include "boot/switch_lm.asm"

[bits 32]
BEGIN_PM:
    call switch_lm
    jmp $

[bits 64]
BEGIN_LM:
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns control to us (if ever)


BOOT_DRIVE db 0 ; It is a good idea to store it in memory because 'dl' may get overwritten

; padding
times 510 - ($-$$) db 0
dw 0xaa55
