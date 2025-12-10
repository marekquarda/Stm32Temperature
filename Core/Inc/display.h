#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "main.h"
#include "stm32l1xx_hal_lcd.h"


// macro for argument "symbol" in function display(), their combinations takes symbols for viewing
#define DOT 		1<<0
#define COLON 	    1<<1
#define BAT_0		1<<2
#define BAT_1		1<<3
#define BAT_2		1<<4
#define BAT_3		1<<5
#define BLINK		1<<6

void display(uint8_t symbol, uint8_t* char_array);
void show();

#endif