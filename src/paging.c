#include "paging.h"
#include <stdint.h>
#include <stddef.h>
//TODO: write a page frame allocator
extern void load_page_directory(uint32_t* directory);
extern void enable_paging(void);
uint32_t page_directory[1024] __attribute__((aligned(4096))); //define a page directory aligned at 4096
uint32_t first_page_table[1024] __attribute__((aligned(4096)));
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
}
