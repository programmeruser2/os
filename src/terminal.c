#include "terminal.h"
#include "string.h"
#include "ports.h" 
#include "memory.h"
#include <stdint.h>
#include <stddef.h>
#define VGA_COMMAND_PORT 0x3d4
#define VGA_DATA_PORT 0x3d5
static uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg <<  4;
}
static uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc |  (uint16_t) color << 8;
}
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
size_t terminal_get_offset(void) {
	// request register is 0x3d4, output register is 0x3d5
	outb(VGA_COMMAND_PORT, 0x0E);
	size_t position = inb(VGA_DATA_PORT);
	position = position << 8;
	outb(VGA_COMMAND_PORT, 0x0F);
	position += inb(VGA_DATA_PORT);
	return position; 
}
void terminal_set_cursor_pos(size_t x, size_t y) {
	uint16_t pos = y * VGA_WIDTH + x;
	outb(VGA_COMMAND_PORT, 0x0E);
	outb(VGA_DATA_PORT, (uint8_t) ((pos >> 8) & 0xFF));
	outb(VGA_COMMAND_PORT, 0x0F);
	outb(VGA_DATA_PORT, (uint8_t) (pos & 0xFF)); 
}
void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xb8000;
	for (size_t y = 0; y < VGA_HEIGHT; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_set_cursor_pos(terminal_column, terminal_row);
}
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
void terminal_scroll(void) {
        for (size_t y = 1; y < VGA_HEIGHT; ++y)
		memory_copy((char*) (y * VGA_WIDTH + 0xb8000), (char*) ((y - 1) * VGA_WIDTH + 0xb8000), VGA_WIDTH);
	terminal_row -= 1;
	terminal_set_cursor_pos(terminal_column, terminal_row);
}
void terminal_putchar(char c) {
	if (c == '\r') {
		terminal_column = 0;
	} else if (c == '\n') {
		terminal_row += 1;
		if (terminal_row == VGA_HEIGHT) {
			terminal_scroll();
		}
	} else {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_scroll();
			}
		}
	}
}
void terminal_write(char* data, size_t size) {
	for (size_t i = 0; i < size; ++i) 
		terminal_putchar(data[i]);
	terminal_set_cursor_pos(terminal_column, terminal_row);
}
void terminal_write_string(char* str) {
	terminal_write(str, strlen(str));
}
void terminal_write_int(int num) {
	char buffer[10];
	terminal_write_string(itoa(num, buffer));
}
void terminal_write_line(char* str) {
	terminal_write_string(str);
	terminal_write_string("\r\n");
}

