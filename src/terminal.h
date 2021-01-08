#ifndef VGA_H
#define VGA_H
#include <stdint.h>
#include <stddef.h>
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
static uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
static uint16_t vga_entry(unsigned char uc, uint8_t color);
size_t terminal_get_offset(void);
void terminal_set_cursor_pos(size_t x, size_t y);
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_scroll(size_t times);
void terminal_putentry_at(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(char* str, size_t size);
void terminal_write_string(char* str);
void terminal_write_int(int num);
void terminal_write_line(char* str);
#endif

