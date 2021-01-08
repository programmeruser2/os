#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#include <stddef.h>
void timer_initialize(size_t frequency, void (*callback)(size_t));
#endif
