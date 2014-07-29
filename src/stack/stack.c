#include "stack/stack.h"

static void softdevice_assertion_handler(uint32_t pc, uint16_t line_num, const uint8_t * file_name)
{
    UNUSED_PARAMETER(pc);
}

/* Handle the Application's BLE Stack events interrupt. This function is called whenever an event is ready to be pulled. */
void SWI2_IRQHandler(void)
{
    QEvt *pe = NULL;
    pe = Q_NEW(QEvt, STACK_SWI2_SIG);
    QF_PUBLISH((QEvt *)pe, NULL);
}

uint32_t stack_softdevice_init(void)
{
    uint32_t err_code;

    // Initialize SoftDevice.
    err_code = sd_softdevice_enable(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, softdevice_assertion_handler);
    if (err_code != NRF_SUCCESS){
        return err_code;
    }

    // Enable BLE event interrupt (interrupt priority has already been set by the stack).
    return sd_nvic_EnableIRQ(SWI2_IRQn);
}

uint32_t stack_softdevice_deinit(void)
{
    uint32_t err_code = sd_softdevice_disable();
    return err_code;
}

/* Pull events from softdevice */
uint32_t stack_pull_events(void)
{
    uint32_t err_code;
    uint32_t evt_id;

    // Pull sys event from SOC.
    for(;;){
        err_code = sd_evt_get(&evt_id);
        if(err_code == NRF_SUCCESS){
            QEvt *pe = NULL;
            pe = Q_NEW(QEvt, STACK_SYS_EVENT_SIG);
            QF_PUBLISH((QEvt *)pe, NULL);
        }else{
            break;
        }
    }

    // Pull ble event from SOC.
    for(;;){
        uint32_t buf[CEIL_DIV(BLE_STACK_EVT_MSG_BUF_SIZE, sizeof(uint32_t))];
        uint16_t evt_len = sizeof(buf);
        err_code = sd_ble_evt_get((uint8_t *)buf, &evt_len);
        
        if(err_code == NRF_SUCCESS){
            stack_ble_evt *pe = NULL;
            pe = Q_NEW(stack_ble_evt, STACK_BLE_EVENT_SIG);

            memcpy(pe->ble_evt, buf, evt_len);

            QF_PUBLISH((QEvt *)pe, NULL);
        }else{
            break;
        }
    }
    
    return NRF_SUCCESS;
}



