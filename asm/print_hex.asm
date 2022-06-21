print_hex:
    pusha                       ; Push all to stack
    mov cx, 0                   ; Reset counter

hex_loop:
    cmp cx, 4                   ; Loop 4 times
    je end                      ;
    mov ax, dx                  ; ax -> 0x1234
    and ax, 0x000f              ; ax -> 0x0004
    add ax, 0x0030              ; Add 48 to N
    cmp ax, 0x0039              ; Check if it is a letter
    jle step2                   ; If no jump to step 2
    add ax, 0x0007              ; If yes add 7

step2:
    mov bx, HEX_OUT + 5         ; Add a offset
    sub bx, cx                  ; Subtract the counter
    mov [bx], al                ; 
    ror dx, 4                   ; Rotate right (0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234)

    add cx, 1                   ; Add one to counter
    jmp hex_loop                ; Loop

HEX_OUT db '0x0000', 0          ; Template

end:
    mov bx, HEX_OUT             ; Print HEX_OUT
    call print                  ;
    call print_nl

    popa                        ; Put back the full stack
    ret                         ; Return back
