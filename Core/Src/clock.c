#include "clock.h"

// handler
RTC_HandleTypeDef time;
// variable
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

// init timer
void initTime(RTC_HandleTypeDef hrtc) {
    time = hrtc;
}

// private methods
void getTime() {
    HAL_RTC_GetTime(&time, &sTime, RTC_FORMAT_BCD);
}

void getDate() {
    HAL_RTC_GetDate(&time, &sDate, RTC_FORMAT_BCD);
}

void getArrayFromBCD(uint8_t bcd, uint8_t *output) {
    output[0] = bcd & 0x0F;
    output[1] = (bcd >> 4) & 0x0F;
}

// public methods
void getFormatTime(uint8_t* hours, uint8_t* minute, uint8_t* second) {
    getArrayFromBCD(sTime.Hours, hours);
    getArrayFromBCD(sTime.Minutes, minute);
    getArrayFromBCD(sTime.Seconds, second);
}

void getFormatDate(uint8_t* day, uint8_t* month, uint8_t* year, uint8_t* weekAday) {
    getArrayFromBCD(sDate.Date, day);
    getArrayFromBCD(sDate.Month, month);
    getArrayFromBCD(sDate.Year, year);
    getArrayFromBCD(sDate.WeekDay, weekAday);
}