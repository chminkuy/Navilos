#ifndef HAL_HALUART_H_
#define HAL_HALUART_H_

void Hal_uart_init(void);
void Hal_uart_putc(char c);
uint8_t Hal_uart_getc(void);

#endif /* HAL_HALUART_H_ */