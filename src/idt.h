#ifndef IDT_H
#define IDT_H
#include <stdint.h>
struct idt_entry_t {
	uint16_t base_low;
	uint16_t selector;
	uint8_t always_zero;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed));
struct idt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
void idt_initialize(void);
#endif
