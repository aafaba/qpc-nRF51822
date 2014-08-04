#include "test_gpio.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"
#include "nrf_soc.h"

#include "driver/log.h"
#include "qm/qm_signals.h"
#include "qp_port.h"

#define BUTTON_0_PIN 16
#define LED_0_PIN 18

void led_init()
{
	nrf_gpio_cfg_output(LED_0_PIN);

}

void led_on()
{
	nrf_gpio_pin_set(LED_0_PIN);
}

void led_off()
{
	nrf_gpio_pin_clear(LED_0_PIN);
}

void led_toggle()
{
	nrf_gpio_pin_toggle(LED_0_PIN);
}


void GPIOTE_IRQHandler()
{

	if ((NRF_GPIOTE->EVENTS_IN[0] == 1) && (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk))
 	{
 		NRF_GPIOTE->EVENTS_IN[0] = 0; //中断事件清零.

 		{
		QEvt *pe = NULL;
		pe = Q_NEW(QEvt, GPIOTE_TOGGLE_SIG);
		QF_PUBLISH((QEvt *)pe, NULL);

		}
	}	
}

void button_init()
{
	nrf_gpiote_event_config(0, BUTTON_0_PIN, NRF_GPIOTE_POLARITY_TOGGLE);

    //must set nvic priority, or else dead lock with rtc
    sd_nvic_SetPriority(GPIOTE_IRQn, NRF_APP_PRIORITY_LOW);
	sd_nvic_EnableIRQ(GPIOTE_IRQn);
	NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos;
}