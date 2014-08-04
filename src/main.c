#include <stdint.h>
#include <string.h>

#include "qm/qm_stack.h"
#include "qm/qm_gpio.h"
#include "qm/qm_connection.h"
#include "qm/qm_security.h"
#include "qm/qm_lbs.h"

#include "driver/serial.h"
#include "base/stack.h"
#include "user/ble_lbs.h"

/* Local-scope objects -----------------------------------------------------*/
static QEvt const *l_qm_stack_QSto[10];      
static QEvt const *l_qm_gpio_QSto[50];     
static QEvt const *l_qm_connection_QSto[50];
static QEvt const *l_qm_security_QSto[10];
static QEvt const *l_qm_lbs_QSto[10];

static QF_MPOOL_EL(QEvt) l_smlPoolSto[50];
static QF_MPOOL_EL(stack_ble_evt) l_stackevt_pool[5];

static QSubscrList    l_subscrSto[MAX_SIG];
/*..........................................................................*/

ble_lbs_t m_lbs;

void services_init(void)
{
    uint32_t err_code;
    ble_lbs_init_t init;
    
    init.led_write_handler = NULL;
    
    err_code = ble_lbs_init(&m_lbs, &init);
}


int main() 
{   
    serial_init();
    
    stack_softdevice_init();
    
    gap_init();
    
    services_init();
    
    advertising_init();
    advertising_start();                 
  
    /* initialize the framework and the underlying RT kernel */
    QF_init();    

    /* instantiate and start the active objects... */
    qm_stack_ctor();
    qm_gpio_ctor();
    qm_connection_ctor();
    qm_security_ctor();
    qm_lbs_ctor();
    
    /* initialize the event pools... */
    QF_poolInit(l_smlPoolSto, sizeof(l_smlPoolSto), sizeof(l_smlPoolSto[0]));
    QF_poolInit(l_stackevt_pool, sizeof(l_stackevt_pool), sizeof(l_stackevt_pool[0]));

    /* init publish-subscribe */
    QF_psInit(l_subscrSto, Q_DIM(l_subscrSto));   
    
                  
    QACTIVE_START(ao_qm_stack,
                  3U,
                  l_qm_stack_QSto, Q_DIM(l_qm_stack_QSto),
                  (void *)0, 0U, 
                  (QEvt *)0);

    QACTIVE_START(ao_qm_gpio,
                  4U,
                  l_qm_gpio_QSto, Q_DIM(l_qm_gpio_QSto),
                  (void *)0, 0U, 
                  (QEvt *)0);
                  
    QACTIVE_START(ao_qm_connection,
                  5U,
                  l_qm_connection_QSto, Q_DIM(l_qm_connection_QSto),
                  (void *)0, 0U, 
                  (QEvt *)0);
                  
    QACTIVE_START(ao_qm_security,
                  6U,
                  l_qm_security_QSto, Q_DIM(l_qm_security_QSto),
                  (void *)0, 0U, 
                  (QEvt *)0);
                  
     QACTIVE_START(ao_qm_lbs,
                  6U,
                  l_qm_lbs_QSto, Q_DIM(l_qm_lbs_QSto),
                  (void *)0, 0U, 
                  (QEvt *)0);

    return QF_run();                              /* run the QF application */
  
}

/**
 * @}
 */
