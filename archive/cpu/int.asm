[BITS 32]
[EXTERN int_handler]
[EXTERN irq_handler]

int_get:
	call int_handler
    add esp, 8     ; deallocate the error code and the interrupt number
    iret           ; pops CS, EIP, EFLAGS and also SS, and ESP if privilege change occurs

irq_get:
    call irq_handler
    add esp, 8
    iret

%macro isr_err 1
GLOBAL isr_%1
isr_%1:
    cli
    push %1
    jmp int_get
%endmacro

%macro isr_no_err 1
GLOBAL isr_%1
isr_%1:
    cli
    push 0
    push %1
    jmp int_get
%endmacro

%macro irq 2
GLOBAL irq_%1
irq_%1:
    cli
    push %1
    push %2
    jmp irq_get
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
irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47

global flush_idt
flush_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret