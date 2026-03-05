#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"

char printf_buf[256];  // 버퍼 선언 추가

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

uint32_t debug_printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsprintf(printf_buf, fmt, args);
    va_end(args);

    return putstr(printf_buf);
}
/* minimal vsprintf implementation */
uint32_t vsprintf(char* buffer, const char* fmt, va_list args)
{
    uint32_t c = 0;

    char ch;
    char* str;
    uint32_t uint;
    uint32_t hex;

    for(uint32_t i = 0; fmt[i]; i++)
    {
        if(fmt[i] == '%')
        {
            i++;
            switch(fmt[i])
            {
                case 'c':
                    ch = (char)va_arg(args, int);
                    buffer[c++] = ch;
                    break;
                case 's':
                    str = va_arg(args, char*);
                    while(*str)
                    {
                        buffer[c++] = *str++;
                    }
                    break;
                case 'd':
                    uint = va_arg(args, uint32_t);
                    c += utoa(buffer + c, uint, utoa_dec);
                    break;
                case 'x':
                    hex = va_arg(args, uint32_t);
                    c += utoa(buffer + c, hex, utoa_hex);
                    break;
                default:
                    buffer[c++] = fmt[i];
            }
        }
        else
        {
            buffer[c++] = fmt[i];
        }
    }
    buffer[c] = '\0';  // null terminator 추가
    return c;  // return 추가
}

uint32_t utoa(char* buffer, uint32_t num, utoa_t base)
{
    uint32_t c = 0;
    int32_t idx = 0;
    char tmp[11];

    if (num == 0) {
        buffer[c++] = '0';
        return c;
    }

    do {
        uint32_t rem = num % base;
        tmp[idx++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
        num /= base;
    } while(num > 0);

    idx--;
    while(idx >= 0)
    {
        buffer[c++] = tmp[idx--];
    }

    return c;
}
