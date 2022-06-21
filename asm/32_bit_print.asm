[bits 32]

; this is how constants are defined
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f ; the color byte for each character

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx] ; [ebx] is the address of our character
    cmp al, 0 ; check if end of string
    je print_string_pm_done

    mov ah, WHITE_ON_BLACK

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret

clear_sc:
    pusha
    mov ecx, 0x7D0
    mov al, ' '
    mov ah, WHITE_ON_BLACK
clear_loop:
    mov edx, VIDEO_MEMORY
    add edx, ecx
    add edx, ecx

    mov [edx], ax

    loop clear_loop
    jmp print_string_pM_done