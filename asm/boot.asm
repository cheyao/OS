[ org 0x7c00 ]                  ; Global offset
mov ah, 0x0e                    ; Print number

mov [BOOT_DRIVE], dl            ; Save dl

mov bp, 0x8000                  ; Stack
mov sp, bp                      ;

mov ah, 0x01                       ; Remove cursor
mov ch, 0x3F
int 0x10

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
; 32 bit
%include '32_bit_print.asm'

LOADING_32: db 'Swiching...', 0
SUCCESS: db 'Booting...', 0
BOOT_DRIVE: db 0

[bits 32]
BEGIN_PM:
    call clear_sc
    mov ebx, SUCCESS
    call print_string_pm

    jmp $

; Padding and magic BIOS number.
times 510 -( $ - $$ ) db 0
dw 0xaa55