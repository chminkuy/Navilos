#include "stdint.h"
#include "Uart.h"
#include "HalUart.h"
#include "HalInterrupt.h"

extern volatile PL011_t* Uart;

static void interrupt_handler(void);

void Hal_uart_init(void)
{
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;

    Uart->uarticr.all = 0x7FF;
    Uart->uartimsc.bits.RXIM = 1;

    Hal_interrupt_enable(UART_INTERRUPT0);
    Hal_interrupt_register_handler(UART_INTERRUPT0, interrupt_handler);
}

static void interrupt_handler(void)
{
    debug_printf("%s\n", __FUNCTION__);
    char c = Hal_uart_getc();
    Hal_uart_putc(c);
}

void Hal_uart_putc(char c)
{
    while(Uart->uartfr.bits.TXFF);
    Uart->uartdr.all = (c & 0xFF);
}

uint8_t Hal_uart_getc(void)
{
    uint32_t data;
    while(Uart->uartfr.bits.RXFE);

    data = Uart->uartdr.all;
    
    if(data & 0xFFFFFF00)
    {
        Uart->uartrsr.all = 0xFF;
        return 0;
    }

    return (uint8_t)(data & 0xFF);
}
