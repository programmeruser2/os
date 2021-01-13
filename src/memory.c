#include "memory.h"
#include <stdint.h>
#include <stddef.h>
void memory_copy(char* source, char* dest, size_t nbytes) {
	for (int i = 0; i < nbytes; ++i) {
		*(dest + i) = *(source + i);
	}
}
void memory_set(uint8_t* dest, uint8_t value, size_t len) {
	uint8_t* ptr = (uint8_t*) dest;
	for(; len != 0; --len) *(ptr++) = value; 
}
