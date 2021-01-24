#include "paging.h"
#include "isr.h"
#include "terminal.h"
#include <stdint.h>
#include <stddef.h>
//TODO: write a page frame allocator
extern void load_page_directory(uint32_t* directory);
extern void enable_paging(void);
uint32_t page_directory[1024] __attribute__((aligned(4096))); //define a page directory aligned at 4096
uint32_t first_page_table[1024] __attribute__((aligned(4096)));
void page_fault_handler(struct registers_t* regs) {
	uint32_t fault_address;
	__asm__("mov %%cr0, %0" : "=r" (fault_address));
	int present = !(regs->err_code & 0x1);
	int rw = regs->err_code & 0x2;
	int user_mode = regs->err_code & 0x4;
	int reserved = regs->err_code & 0x8;
	int id = regs->err_code & 0x10;
	terminal_write_string("Page fault: ");
	if (present) terminal_write_string("present ");
	if (rw) terminal_write_string("read-only ");
	if (user_mode) terminal_write_string("user-mode ");
	if (reserved) terminal_write_string("reserved ");
	terminal_write_string("at ");
	terminal_write_int(fault_address); //TODO: print hex instead of decimal
	terminal_write_line("");
	for(;;) __asm__("hlt");
}
void paging_initialize(void) {
	for (size_t i = 0; i < 1024; ++i) {
		//flags: supervisor (kernel only), write enabled, not present
		page_directory[i] = 0x00000002; 
	}
	for (uint32_t i = 0; i < 1024; ++i) {
		//attributes: supervisor level, read/write, present
		first_page_table[i] = (i * 0x1000) | 3;
	}
	//attributes: supervisor level, read/write, present
	page_directory[0] = ((uint32_t) first_page_table) | 3;
	load_page_directory(page_directory);
	enable_paging();
	//register page fault handler
	register_interrupt_handler(14, page_fault_handler);
}
