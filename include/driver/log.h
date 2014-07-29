#ifndef  ____DRIVER_LOG_H__
#define  ____DRIVER_LOG_H__

#include <stdio.h>

#define __DEBUG__

#ifdef __DEBUG__
#define LOG(format, ...) printf(format"\n\r", ##__VA_ARGS__)
#else
#define LOG(format, ...)
#endif

#endif
