[bits 32]

switch_lm:
    ; check A10 Line
    pushad
    mov edi,0x112345  ;odd megabyte address.
    mov esi,0x012345  ;even megabyte address.
    mov [esi],esi     ;making sure that both addresses contain diffrent values.
    mov [edi],edi     ;(if A20 line is cleared the two pointers would point to the address 0x012345 that would contain 0x112345 (edi))
    cmpsd             ;compare addresses to see if the're equivalent.
    popad

    jne enable_paging        ;if not equivalent , A20 line is set.
    ; If there isn't any, set it up
    in al, 0x92
    or al, 2
    out 0x92, al

enable_paging:
    mov edi, PAGING_OFFSET    ; Set the destination index to 0x1000.
    mov cr3, edi              ; Set control register 3 to the destination index.
    xor eax, eax              ; Nullify the A-register.
    mov ecx, 4096             ; Set the C-register to 4096.
    rep stosd                 ; Clear the memory.
    mov edi, cr3              ; Set the destination index to control register 3.

    ; Make PML4T, PDPT, PDT and PT
    mov DWORD [edi], 0x000C8FFF      ; Set the uint32_t at the destination index to 0x2003.
    add edi, 0x1000                  ; Add 0x1000 to the destination index.
    mov DWORD [edi], 0x000C9FFF      ; Set the uint32_t at the destination index to 0x3003.
    add edi, 0x1000                  ; Add 0x1000 to the destination index.
    mov DWORD [edi], 0x000CAFFF      ; Set the uint32_t at the destination index to 0x4003.
    add edi, 0x1000                  ; Add 0x1000 to the destination index.

    ; Setup loop
    mov ebx, 0x00000003          ; Set the B-register to 0x00000003.
    mov ecx, 512                 ; Set the C-register to 512.

.SetEntry:
    mov DWORD [edi], ebx         ; Set the uint32_t at the destination index to the B-register.
    add ebx, 0x1000              ; Add 0x1000 to the B-register.
    add edi, 8                   ; Add eight to the destination index.
    loop .SetEntry               ; Set the next entry.
    ; PAE-paging enable
    mov eax, cr4                 ; Set the A-register to control register 4.
    or eax, 1 << 5               ; Set the PAE-bit, which is the 6th bit (bit 5).
    mov cr4, eax                 ; Set control register 4 to the A-register.
    ; LM-bit
    mov ecx, 0xC0000080          ; Set the C-register to 0xC0000080, which is the EFER MSR.
    rdmsr                        ; Read from the model-specific register.
    or eax, 1 << 8               ; Set the LM-bit which is the 9th bit (bit 8).
    wrmsr                        ; Write to the model-specific register.
    ; Enable paging -- crash here
    mov eax, cr0                 ; Set the A-register to control register 0.
    or eax, 1 << 31              ; Set the PG-bit, which is the 32nd bit (bit 31).
    mov cr0, eax                 ; Set control register 0 to the A-register.

    ret