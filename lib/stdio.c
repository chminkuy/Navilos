#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"

uint32_t putstr(const char* str)
{
    uint32_t count = 0;

    while(*str)
    {
        Hal_uart_putc(*str++);
        count++;
    }

    return count;
}