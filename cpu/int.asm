[BITS 32]
[EXTERN int_handler]

int_get:
    SAVE_REGS
	call int_handler
    RESTORE_REGS
    add esp, 8     ; deallocate the error code and the interrupt number
    iret           ; pops CS, EIP, EFLAGS and also SS, and ESP if privilege change occurs

%macro isr_err 1
GLOBAL isr_%1
isr_%1:
    push %1
    jmp int_get
%endmacro

%macro isr_no_err 1
GLOBAL isr_%1
isr_%1:
    push 0
    push %1
    jmp int_get
%endmacro

isr_no_err 0
isr_no_err 1
isr_no_err 2
isr_no_err 3
isr_no_err 4
isr_no_err 5
isr_no_err 6
isr_no_err 7
isr_err    8
isr_no_err 9
isr_err    10
isr_err    11
isr_err    12
isr_err    13
isr_err    14
isr_no_err 15
isr_no_err 16
isr_err    17
isr_no_err 18
isr_no_err 19
isr_no_err 20
isr_no_err 21
isr_no_err 22
isr_no_err 23
isr_no_err 24
isr_no_err 25
isr_no_err 26
isr_no_err 27
isr_no_err 28
isr_no_err 29
isr_err    30
isr_no_err 31

%macro	SAVE_REGS 0
        pushad
        push ds ;those registers are 16 bit but they are pushed as 32 bits here
        push es
        push fs
        push gs

        push ebx
        mov bx, 0x10 ; load the kernel data segment descriptor
        mov ds, bx
        mov es, bx
        mov fs, bx
        mov gs, bx
        pop ebx
%endmacro

%macro	RESTORE_REGS 0
        pop gs
        pop fs
        pop es
        pop ds
        popad
%endmacro

global flush_idt
flush_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret