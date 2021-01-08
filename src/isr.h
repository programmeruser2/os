#ifndef ISR_H
#define ISR_H
#include <stdint.h>

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define PIC_MASTER_COMMAND_PORT 0x20
#define PIC_MASTER_DATA_PORT 0x21
#define PIC_SLAVE_COMMAND_PORT 0xA0
#define PIC_SLAVE_DATA_PORT 0xA1

struct registers_t {
	uint32_t ds; //data segment selector
	uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; // registers pushed by pusha
	uint32_t int_number, err_code; //interrupt number and error code
	uint32_t eip, cs, eflags, esp, ss; //automatically pushed by processor
};
typedef void (*isr_t)(struct registers_t*);
void register_interrupt_handler(uint8_t n, isr_t handler);
#endif
