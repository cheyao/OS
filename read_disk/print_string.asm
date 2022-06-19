print:
    pusha                       ; Push all to stack

start:
    mov al, [bx]                ; Move the value at bx to al
    cmp al, 0                   ; See if it is the end of the string
    je done                     ; If yes, jump to done

    mov ah, 0x0e                ; Print mode
    int 0x10                    ; Print

    add bx, 1                   ; Add one to bx
    jmp start                   ; Loop

done:
    popa                        ; Pop all from stack to registers
    ret                         ; Return back

print_nl:
    pusha                       ; Push all to stack
    
    mov ah, 0x0e                ; Print mode
    mov al, 0x0a                ; newline char
    int 0x10                    ; Print
    mov al, 0x0d                ; carriage return
    int 0x10                    ; Print
    
    popa                        ; Pop all from stack to registers
    ret                         ; Return back