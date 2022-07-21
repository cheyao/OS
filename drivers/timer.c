#include "drivers/timer.h"
#include "kernel/functions.h"
#include "cpu/isr.h"
#include "cpu/idt.h"
#include "drivers/ports.h"

u32int tick;
u32int time;

void update_clock();

void timer_callback(u8int int_no) {
    tick++;
    UNUSED(int_no);
    if (tick % 60 == 0) {
        update_clock();
    }
}

// Updates the clock (Increases the time and prints it)
void update_clock() {
    time++;

    print_time(75, 0);
}

// For printing to the top right, use col = 75, row = 0
// For printing to the cursor, use col = -1, row = -1
void print_time(int col, int row) {
    char* time_ascii = "00:00";

    time_ascii[4] = (char) ('0' + time % 10);
    time_ascii[3] = (char) ('0' + time % 60 / 10);
    time_ascii[1] = (char) ('0' + time / 60 % 10);
    time_ascii[0] = (char) ('0' + time / 60 / 10);

    if (col < 0 || row < 0) kprint(time_ascii);
    else kprint_at(time_ascii, col, row);
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
