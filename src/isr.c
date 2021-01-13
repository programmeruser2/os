#include "isr.h"
#include "terminal.h"
#include "ports.h"

char* exception_messages[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",

	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",

	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};
isr_t interrupt_handlers[256];
void isr_handler(struct registers_t* regs) {
	terminal_write_string("Recieved interrupt: ");
	terminal_write_int(regs->int_number);
	terminal_write_line("");
	if (interrupt_handlers[regs->int_number] != NULL) {
		isr_t handler = interrupt_handlers[regs->int_number];
		handler(regs);
	} else {
		terminal_write_line(exception_messages[regs->int_number]);
		terminal_write_line("Exception recieved. System halted.");
		//halt the processor
		for(;;) asm volatile("hlt");
	}
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
	interrupt_handlers[n] = handler;
}

void irq_handler(struct registers_t* regs) {
	//send end of interrupt (EOI) signal to PICs
	//if interrupt involved the slave
	if (regs->int_number >= 40)
		outb(PIC_SLAVE_COMMAND_PORT, 0x20);
	//send reset signal to master
	outb(PIC_MASTER_COMMAND_PORT, 0x20);
	if (interrupt_handlers[regs->int_number] != 0) {
		isr_t handler = interrupt_handlers[regs->int_number];
		handler(regs);
	}
}
