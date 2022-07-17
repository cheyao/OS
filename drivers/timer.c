#include "timer.h"
#include "../kernel/functions.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "ports.h"

u32int tick;
u32int time;
void clock();

void timer_callback(u8int int_no) {
    tick++;
    UNUSED(int_no);
    if (tick % 60 == 0) {
        clock();
    }
}

void clock() {
    time++;
    char* time_ascii = "00:00";
    time_ascii[4] = '0' + time % 10; // 02 % 10 = 2
    time_ascii[3] = '0' + time % 60 / 10;
    time_ascii[1] = '0' + time / 60 % 10;
    time_ascii[0] = '0' + time / 60 / 10;
    kprint_at(time_ascii, 75, 0);
}

void timer_wait(u32int ticks) {
    u32int eticks;

    eticks = tick + ticks;
    while(tick < eticks);
}

void init_timer(u32int freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32int divisor = 1193180 / freq;
    u8int low  = (u8int)(divisor & 0xFF);
    u8int high = (u8int)( (divisor >> 8) & 0xFF);
    /* Send the command */
    outb(0x43, 0x36); /* Command port */
    outb(0x40, low);
    outb(0x40, high);
}
