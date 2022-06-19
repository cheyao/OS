[ org 0x7c00 ]                  ; Global offset
mov ah, 0x0e                    ; Print number

mov bp, 0x8000                  ; Stack
mov sp, bp                      ;

read_file:
    pusha

    mov ah, 0x02
    mov dl, 0
    mov ch, 3
    mov dh, 1
    mov cl, 4
    mov al, 5

    mov bx, 0xa000
    mov es, bx
    mov bx, 0x1234

    int 0x02

    jc error

    popa

error:
    pusha
    mov bx, ERROR
    call print
    call print_nl
    popa

jmp $                           ; Infinite loop

ERROR: db 'ERROR! ', 0

%include 'print_hex.asm'
%include 'print_string.asm'

; Padding and magic BIOS number.
times 510 -( $ - $$ ) db 0
dw 0xaa55