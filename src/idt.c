#include "idt.h"
#include "ports.h"
#include <stdint.h>

#define PIC_MASTER_COMMAND_PORT 0x20
#define PIC_MASTER_DATA_PORT 0x21
#define PIC_SLAVE_COMMAND_PORT 0xA0
#define PIC_SLAVE_DATA_PORT 0xA1

struct idt_entry_t idt_entries[256] = { 0 }; //fill with zeroes
struct idt_ptr_t idt_ptr;

extern void load_idt(uint32_t idt);

void create_idt_entry(struct idt_entry_t* idt_entry_ptr, uint32_t base, uint16_t selector, uint8_t flags) {
	idt_entry_ptr->base_low = base & 0xFFFF;
	idt_entry_ptr->base_high = (base >> 16) & 0xFFFF;
	idt_entry_ptr->selector = selector;
	idt_entry_ptr->always_zero = 0;
	//uncomment below when getting to user mode to set privilege level to 3
	idt_entry_ptr->flags = flags /* | 0x60 */; 
}
void idt_initialize(void) {
	#define DEFINE_IDT_ENTRY(n) create_idt_entry(&idt_entries[n], (uint32_t) isr##n, 0x08, 0x8E)
	#define DEFINE_IRQ_ENTRY(n, i) create_idt_entry(&idt_entries[i], (uint32_t) irq##n, 0x08, 0x8E)
	idt_ptr.limit = sizeof(struct idt_entry_t) * 256 - 1;
	idt_ptr.base = (uint32_t) &idt_entries;
	extern void isr0(void);
	extern void isr1(void);
	extern void isr2(void);
	extern void isr3(void);
	extern void isr4(void);
	extern void isr5(void);
	extern void isr6(void);
	extern void isr7(void);
	extern void isr8(void);
	extern void isr9(void);
	extern void isr10(void);
	extern void isr11(void);
	extern void isr12(void);
	extern void isr13(void);
	extern void isr14(void);
	extern void isr15(void);
	extern void isr16(void);
	extern void isr17(void);
	extern void isr18(void);
	extern void isr19(void);
	extern void isr20(void);
	extern void isr21(void);
	extern void isr22(void);
	extern void isr23(void);
	extern void isr24(void);
	extern void isr25(void);
	extern void isr26(void);
	extern void isr27(void);
	extern void isr28(void);
	extern void isr29(void);
	extern void isr30(void);
	extern void isr31(void);

	extern void irq0(void);
	extern void irq1(void);
	extern void irq2(void);
	extern void irq3(void);
	extern void irq4(void);
	extern void irq5(void);
	extern void irq6(void);
	extern void irq7(void);
	extern void irq8(void);
	extern void irq9(void);
	extern void irq10(void);
	extern void irq11(void);
	extern void irq12(void);
	extern void irq13(void);
	extern void irq14(void);
	extern void irq15(void);

	//remapping the PIC
	outb(PIC_MASTER_COMMAND_PORT, 0x11);
	outb(PIC_SLAVE_COMMAND_PORT, 0xA1);
	outb(PIC_MASTER_COMMAND_PORT, 0x11);
	outb(PIC_SLAVE_COMMAND_PORT, 0x11);
	outb(PIC_MASTER_DATA_PORT, 0x20);
	outb(PIC_SLAVE_DATA_PORT, 0x28);
	outb(PIC_MASTER_DATA_PORT, 0x04);
	outb(PIC_SLAVE_DATA_PORT, 0x02);
	outb(PIC_MASTER_DATA_PORT, 0x01);
	outb(PIC_SLAVE_DATA_PORT, 0x01);
	outb(PIC_MASTER_DATA_PORT, 0x0);
	outb(PIC_SLAVE_DATA_PORT, 0x0);

	DEFINE_IDT_ENTRY(0);
	DEFINE_IDT_ENTRY(1);
	DEFINE_IDT_ENTRY(2);
	DEFINE_IDT_ENTRY(3);
	DEFINE_IDT_ENTRY(4);
	DEFINE_IDT_ENTRY(5);
	DEFINE_IDT_ENTRY(6);
	DEFINE_IDT_ENTRY(7);
	DEFINE_IDT_ENTRY(8);
	DEFINE_IDT_ENTRY(9);
	DEFINE_IDT_ENTRY(10);
	DEFINE_IDT_ENTRY(11);
	DEFINE_IDT_ENTRY(12);
	DEFINE_IDT_ENTRY(13);
	DEFINE_IDT_ENTRY(14);
	DEFINE_IDT_ENTRY(15);
	DEFINE_IDT_ENTRY(16);
	DEFINE_IDT_ENTRY(17);
	DEFINE_IDT_ENTRY(18);
	DEFINE_IDT_ENTRY(19);
	DEFINE_IDT_ENTRY(20);
	DEFINE_IDT_ENTRY(21);
	DEFINE_IDT_ENTRY(22);
	DEFINE_IDT_ENTRY(23);
	DEFINE_IDT_ENTRY(24);
	DEFINE_IDT_ENTRY(25);
	DEFINE_IDT_ENTRY(26);
	DEFINE_IDT_ENTRY(27);
	DEFINE_IDT_ENTRY(28);
	DEFINE_IDT_ENTRY(29);
	DEFINE_IDT_ENTRY(30);
	DEFINE_IDT_ENTRY(31);

	DEFINE_IRQ_ENTRY(0, 32);
	DEFINE_IRQ_ENTRY(1, 33);
	DEFINE_IRQ_ENTRY(2, 34);
	DEFINE_IRQ_ENTRY(3, 35);
	DEFINE_IRQ_ENTRY(4, 36);
	DEFINE_IRQ_ENTRY(5, 37);
	DEFINE_IRQ_ENTRY(6, 38);
	DEFINE_IRQ_ENTRY(7, 39);
	DEFINE_IRQ_ENTRY(8, 40);
	DEFINE_IRQ_ENTRY(9, 41);
	DEFINE_IRQ_ENTRY(10, 42);
	DEFINE_IRQ_ENTRY(11, 43);
	DEFINE_IRQ_ENTRY(12, 44);
	DEFINE_IRQ_ENTRY(13, 45);
	DEFINE_IRQ_ENTRY(14, 46);
	DEFINE_IRQ_ENTRY(15, 47);
	load_idt((uint32_t) &idt_ptr);

	#undef DEFINE_IDT_ENTRY
	#undef DEFINE_IRQ_ENTRY
}

