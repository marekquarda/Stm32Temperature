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

void getTime(uint8_t hours, uint8_t minute, uint8_t second) {
    HAL_RTC_GetTime(&time, &sTime, RTC_FORMAT_BCD);
    hours = sTime.Hours;
    minute = sTime.Minutes;
    second = sTime.Seconds;
}

void getDate(uint8_t day, uint8_t month, uint8_t year, uint8_t weekAday) {
    HAL_RTC_GetDate(&time, &sDate, RTC_FORMAT_BCD);
    day = sDate.Date;
    month = sDate.Month;
    year = sDate.Year;
    weekAday = sDate.WeekDay;
}