#include "clock.h"

RTC_HandleTypeDef time;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;



void initTime(RTC_HandleTypeDef hrtc) {
    time = hrtc;
}

void getTime(void) {
    HAL_RTC_GetTime(&time, &sTime, RTC_FORMAT_BCD);
}

void getDate(void) {
    HAL_RTC_GetDate(&time, &sDate, RTC_FORMAT_BCD);
}