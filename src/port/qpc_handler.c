#include "qp_port.h"
#include "app_util.h"

#include "driver/log.h"

/* QPC Handlers */

/*..........................................................................*/
/* start rtc1 to to kick off QF tick */
void QF_onStartup(void) 
{
	LOG("QF_onStartup");
	rtc1_init(); 
}

/*..........................................................................*/
void QF_onCleanup(void) 
{
}

/*..........................................................................*/
/* called with app interrupts disabled, so we enable app interrupts first */
void QF_onIdle(void) 
{       
  QF_INT_ENABLE();
  QF_CPU_SLEEP();
}

/*..........................................................................*/
void Q_onAssert(char const Q_ROM * const file, int line)
{    
    LOG("Q_onAssert");
}
