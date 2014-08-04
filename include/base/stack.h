#ifndef __DEVICE_STACK_HELPER_H__
#define __DEVICE_STACK_HELPER_H__

#include "common.h"

uint32_t stack_softdevice_init(void);
uint32_t stack_softdevice_deinit(void);

uint32_t stack_pull_events(void);

#endif
