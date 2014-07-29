#include <stdint.h>
#include <string.h>

#include "qm/qm_stack.h"
#include "driver/serial.h"
#include "stack/stack.h"

/* Local-scope objects -----------------------------------------------------*/
static QEvt const *l_sm_stack_QSto[10];      

static QF_MPOOL_EL(QEvt) l_smlPoolSto[10];
static QF_MPOOL_EL(stack_ble_evt) l_stackevt_pool[5];

static QSubscrList    l_subscrSto[MAX_SIG];
/*..........................................................................*/
int main() 
{   
    serial_init();
    
    stack_softdevice_init();
    
    gap_init();
    
    advertising_init();
    advertising_start();                 
  
    /* initialize the framework and the underlying RT kernel */
    QF_init();    

    /* instantiate and start the active objects... */
    qm_stack_ctor();
    
    /* initialize the event pools... */
    QF_poolInit(l_smlPoolSto, sizeof(l_smlPoolSto), sizeof(l_smlPoolSto[0]));
    QF_poolInit(l_stackevt_pool, sizeof(l_stackevt_pool), sizeof(l_stackevt_pool[0]));

    /* init publish-subscribe */
    QF_psInit(l_subscrSto, Q_DIM(l_subscrSto));   
    
                  
    QACTIVE_START(ao_qm_stack,
                  3U,
                  l_sm_stack_QSto, Q_DIM(l_sm_stack_QSto),
                  (void *)0, 0U, 
                  (QEvt *)0);


    return QF_run();                              /* run the QF application */
  
}

/**
 * @}
 */
