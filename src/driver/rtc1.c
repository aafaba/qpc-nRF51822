#include "driver/rtc1.h"
#include "driver/config.h"

#include "app_util.h"
#include "nrf_gpio.h"
#include "qp_port.h"
#include "qm/qm_signals.h"

#define LED_RGB_GREEN  21

#define LFCLK_FREQUENCY           (32768UL)                               /**< LFCLK frequency in Hertz, constant. */
#define COUNTER_PRESCALER         ((LFCLK_FREQUENCY/RTC1_FREQUENCY) - 1)   /* f = LFCLK/(prescaler + 1) */


/* rtc1 clock tick ISR */
void RTC1_IRQHandler(void) 
{                       
    if(NRF_RTC1->EVENTS_TICK != 0){
        NRF_RTC1->EVENTS_TICK = 0;
    }
    
    /* drive QF */
    QF_TICK_X(0U, (void *)0);
}


void rtc1_init(void)
{
    NVIC_EnableIRQ(RTC1_IRQn);
    
    NRF_RTC1->PRESCALER = COUNTER_PRESCALER;
    NRF_RTC1->EVTENSET = RTC_EVTENSET_TICK_Msk;
    NRF_RTC1->INTENSET = RTC_INTENSET_TICK_Msk;
    
    NVIC_SetPriority(RTC1_IRQn, APP_IRQ_PRIORITY_LOW);
    
    NRF_RTC1->TASKS_START = 1;
}

void rtc1_deinit(void)
{
    NRF_RTC1->TASKS_STOP = 1;
}
