#ifndef LIB_STDIO_H_
#define LIB_STDIO_H_

#include "stdarg.h"

typedef enum utoa_t
{
    utoa_dec = 10,
    utoa_hex = 16
} utoa_t;
    
uint32_t putstr(const char* str);
uint32_t debug_printf(const char* fmt, ...);
uint32_t vsprintf(char* buffer, const char* fmt, va_list args);
uint32_t utoa(char* buffer, uint32_t num, utoa_t base);

#endif /* LIB_STDIO_H_ */