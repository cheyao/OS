[bits 32]

switch_lm:
    ; check A20 Line
    pushad
    mov edi,0x112345
    mov esi,0x012345
    mov [esi],esi
    mov [edi],edi
    cmpsd
    popad

    jne enable_paging
    ; If there isn't any, set it up
    in al, 0x92
    or al, 2
    out 0x92, al

    jmp switch_lm

enable_paging:
    mov edi, PAGING_OFFSET
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd
    mov edi, cr3

    ; Make PML4T, PDPT, PDT and PT
    mov DWORD [edi], 0x00002003
    add edi, 0x1000
    mov DWORD [edi], 0x00003003
    add edi, 0x1000
    mov DWORD [edi], 0x00004003
    add edi, 0x1000

    ; Setup loop
    mov ebx, 0x00000003
    mov ecx, 512

.SetEntry:
    mov DWORD [edi], ebx
    add ebx, 0x1000
    add edi, 8
    loop .SetEntry
    ; PAE-paging enable
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax
    ; LM-bit
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    ; Enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    mov byte [gdt_code.code_limit], 10101111b
    lgdt [gdt_descriptor]

    jmp CODE_SEG:init_lm ; Looooooooooooong jump

[bits 64]
init_lm:    ; Well the long jump wasn't very long
    mov ax, DATA_SEG    ; Make everything point to the data seg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rbp, 0xF0010  ; Can't make it more then 0xF0010 or crash
    mov rsp, rbp

    call BEGIN_LM
