#include "driver/log.h"
#include "simple_uart.h"

/* this function is used by C lib's printf() function, should enable MicroLib in Arm Keil option page*/
int fputc(int ch, FILE *f)
{
    simple_uart_put(ch);
    return ch;
}


