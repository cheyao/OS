[ org 0x7c00 ]                  ; Global offset
mov ah, 0x0e                    ; Print number

mov [BOOT_DRIVE], dl            ; Save dl

mov bp, 0x8000                  ; Stack
mov sp, bp                      ;

mov bx, 0x9000                  ; Load 5 sectors to 0x0000:0x9000 (ES:BX)
mov dh, 1                       ; from the boot disk.
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call print_hex

mov dx, [0x9000 + 2]
call print_hex

jmp $

%include 'print_hex.asm'
%include 'print_string.asm'
%include 'read.asm'

BOOT_DRIVE: db 0

; Padding and magic BIOS number.
times 510 -( $ - $$ ) db 0
dw 0xaa55

times 1 dw 0xdada
times 1 dw 0xface