[ org 0x7c00 ]                  ; Global offset
mov ah, 0x0e                    ; Print number

mov [BOOT_DRIVE], dl            ; Save dl

mov bp, 0x8000                  ; Stack
mov sp, bp                      ;

; mov bx, 0x9000                  ; Load 5 sectors to 0x0000:0x9000 (ES:BX)
; mov dh, 1                       ; from the boot disk.
; mov dl, [BOOT_DRIVE]
; call disk_load

call print_nl
mov bx, LOADING_32
call print
call print_nl

call switch_to_pm

%include 'print_hex.asm'
%include 'print_string.asm'
%include 'read.asm'
%include 'gdt.asm'
%include 'swich.asm'
%include '32_bit_print.asm'

LOADING_32: db 'Swiching to 32 bit mode...', 0
SUCCESS: db 'Success', 0
BOOT_DRIVE: db 0

[bits 32]
BEGIN_PM:
    mov ebx, SUCCESS
    call print_string_pm
    jmp $

; Padding and magic BIOS number.
times 510 -( $ - $$ ) db 0
dw 0xaa55