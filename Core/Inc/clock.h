#ifndef __CLOCK_H
#define __CLOCK_H

#include "main.h"
#include "stm32l1xx_hal_rtc.h"


void initTime(RTC_HandleTypeDef time);
void getTime(void);
void getDate(void);

#endif