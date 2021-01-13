#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include <stddef.h>
void timer_callback(size_t tick) {
	terminal_write_int((int) tick);
	terminal_write_line("");
}
void kernel_main(void) {
	terminal_initialize();
	gdt_initialize();
	idt_initialize();
	terminal_write_line("Hello World");
	//asm volatile("int $0x3");
	//asm volatile("int $0x4");
	//enable interrupts
	asm volatile("sti");
	terminal_write_line("Starting timer...");
	timer_initialize(50, timer_callback); //initialize timer to 50 Hz
	for(;;) asm volatile("hlt");
}
