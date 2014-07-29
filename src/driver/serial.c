#include "driver/serial.h"
#include "driver/config.h"
#include "simple_uart.h"

void serial_init(void)
{
    simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
}

