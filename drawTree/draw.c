#include "common.h"

void termial_init()
{
    printf("\33[2J");   // clear screen
    printf("\33[?25l"); // hide cursor
}

void terminal_draw_char(int x, int y, uint8_t* s)
{
    printf("\33[%d;%dH", y, x);
    printf("%s", s);
}
