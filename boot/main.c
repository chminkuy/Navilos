#include "stdint.h"

#include "HalUart.h"
#include "HalInterrupt.h"
#include "stdio.h"

static void Hw_init(void);
static void Printf_test(void);

void _exit(int status)
{
    while(1);
}

void main(void)
{
    Hw_init();

    uint32_t i = 100;

    while(i--)
    {
        Hal_uart_putc('N');
    }
    Hal_uart_putc('\n');

    putstr("Hello, Navilos!\n");

    Printf_test();

    while(1);
}

static void Hw_init(void)
{
    
    Hal_interrupt_init();
    Hal_uart_init();
}

static void Printf_test(void)
{
    char* str = "printf pointer test";
    char* nullptr = 0;
    uint32_t i = 11;

    debug_printf("%s\n", "hello printf!");
    debug_printf("string: %s\n", str);
    debug_printf("nullptr: %s\n", nullptr);
    debug_printf("decimal: %d\n", i);
    debug_printf("hex: 0x%x\n", i);

}
