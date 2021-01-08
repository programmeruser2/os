#include "gdt.h"
#include "terminal.h"
#include <stdint.h>
extern void load_gdt(uint32_t gdt);
struct gdt_entry_t gdt_entries[5];
struct gdt_ptr_t gdt_ptr;
void create_gdt_entry(struct gdt_entry_t* gdt_entry_ptr, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
	gdt_entry_ptr->base_low = (base & 0xFFFF);
	gdt_entry_ptr->base_middle = (base >> 16) & 0xFF;
	gdt_entry_ptr->base_high = (base >> 24) & 0xFF;

	gdt_entry_ptr->limit_low = (limit & 0xFFFF);
	gdt_entry_ptr->granularity = (limit >> 16) & 0x0F;

	gdt_entry_ptr->granularity = granularity | 0xF0;
	gdt_entry_ptr->access = access; 
}
void gdt_initialize(void) {
	gdt_ptr.limit = (sizeof(struct gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (uint32_t) &gdt_entries;
	create_gdt_entry(&gdt_entries[0], 0, 0, 0, 0); // null segment
	create_gdt_entry(&gdt_entries[1], 0, 0xFFFFFFFF, 0x9A, 0xCF); // code segment
	create_gdt_entry(&gdt_entries[2], 0, 0xFFFFFFFF, 0x92, 0xCF); // data segment
	create_gdt_entry(&gdt_entries[3], 0, 0xFFFFFFFF, 0xFA, 0xCF ); // user mode code segment
	create_gdt_entry(&gdt_entries[4], 0, 0xFFFFFFFF, 0xF2, 0xCF); // user mode data segment
	load_gdt((uint32_t) &gdt_ptr);
}
