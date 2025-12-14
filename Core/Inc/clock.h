#ifndef __CLOCK_H
#define __CLOCK_H

#include "main.h"
#include "stm32l1xx_hal_rtc.h"


void initTime(RTC_HandleTypeDef time);
void getTime(uint8_t hours, uint8_t minute, uint8_t second);
void getDate(uint8_t day, uint8_t month, uint8_t year, uint8_t weekAday);

#endif