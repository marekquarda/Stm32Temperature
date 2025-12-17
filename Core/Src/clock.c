/*
 * @file        clock.c
 * @brief       Clock Library
 * @author      Marek Quarda
 * @version     1.0.0
 */

#include "clock.h"

void getArrayFromBCD(uint8_t bcd, uint8_t *output) {
    output[0] = bcd & 0x0F;
    output[1] = (bcd >> 4) & 0x0F;
}

// public methods
void getFormatTime(RTC_TimeTypeDef myTime, uint8_t* hours, uint8_t* minute, uint8_t* second) {
    getArrayFromBCD(myTime.Hours, hours);
    getArrayFromBCD(myTime.Minutes, minute);
    getArrayFromBCD(myTime.Seconds, second);
}

void getFormatDate(RTC_DateTypeDef myDate, uint8_t* day, uint8_t* month, uint8_t* year, uint8_t* weekAday) {
    getArrayFromBCD(myDate.Date, day);
    getArrayFromBCD(myDate.Month, month);
    getArrayFromBCD(myDate.Year, year);
    getArrayFromBCD(myDate.WeekDay, weekAday);
}