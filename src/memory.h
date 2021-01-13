#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include <stddef.h>
void memory_copy(char* source, char* dest, size_t nbytes);
void memory_set(uint8_t* dest, uint8_t value, size_t len);
#endif
