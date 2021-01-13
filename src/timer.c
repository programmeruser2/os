#include "timer.h"
#include "isr.h"
#include "ports.h"
#include <stdint.h>
#include <stddef.h>

size_t timer_tick = 0;
void (*timer_set_callback)(size_t);
void timer_irq_callback(struct registers_t* regs) {
	++timer_tick;
	timer_set_callback(timer_tick);
}
void timer_initialize(size_t frequency, void (*callback)(size_t)) {
	register_interrupt_handler(IRQ0, timer_irq_callback);

	//set callback
	timer_set_callback = callback;

	//sent value is the value that the input clock (1193180 Hz) by
	size_t divisor =  1193180 / frequency;

	//send command byte
	outb(0x43, 0x36);

	//divisor has to be sent bytewise
	outb(0x40, (uint8_t) (divisor & 0xFF));
	outb(0x40, (uint8_t) ((divisor >> 8) & 0xFF));
}
