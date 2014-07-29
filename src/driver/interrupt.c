#include "driver/interrupt.h"
#include "nrf_soc.h"

static volatile uint8_t critical_region_nested_cnt = 0;

void nrf51822_int_disable(void)
{
	uint8_t IS_NESTED_CRITICAL_REGION = 0;
	uint32_t err_code = sd_nvic_critical_region_enter(&IS_NESTED_CRITICAL_REGION);
	if (err_code == NRF_ERROR_SOFTDEVICE_NOT_ENABLED)                               
    {                                                                               
        __disable_irq();                                                            
    }                                                                               
    
    if(IS_NESTED_CRITICAL_REGION)
    {
    	critical_region_nested_cnt++;
    }
}

void nrf51822_int_enable(void)
{
	uint8_t IS_NESTED_CRITICAL_REGION = 0;
	if(critical_region_nested_cnt)
	{
		IS_NESTED_CRITICAL_REGION = 1;
		critical_region_nested_cnt--;
	}
  	uint32_t err_code = sd_nvic_critical_region_exit(IS_NESTED_CRITICAL_REGION);
}

void nrf51822_power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
}
