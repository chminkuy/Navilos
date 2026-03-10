// Handler.c

#include "stdbool.h"
#include "stdint.h"
#include "HalInterrupt.h"

__attribute__ ((interrupt("IRQ"))) void IRQ_handler(void)
{
    Hal_interrupt_run_handler();
}

__attribute__ ((interrupt("FIQ"))) void FIQ_handler(void)
{
    // FIQ handler implementation (if needed)
    while(1);
}

