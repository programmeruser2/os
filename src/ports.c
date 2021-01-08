#include "ports.h"
#include <stdint.h>
uint8_t inb(uint16_t port) {
	uint8_t result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}
void outb(uint16_t port, uint8_t data) {
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
uint16_t inw(uint16_t port) {
        uint16_t result;
        __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
        return result;
}
void outw(uint16_t port, uint16_t data) {
        __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

