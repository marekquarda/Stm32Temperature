#ifndef __CLOCK_H
#define __CLOCK_H

#include "main.h"
#include "stm32l1xx_hal_rtc.h"


void initTime(RTC_HandleTypeDef time);
void getFormatTime(uint8_t* hours, uint8_t* minute, uint8_t* second);
void getFormatDate(uint8_t* day, uint8_t* month, uint8_t* year, uint8_t* weekAday);

#endif