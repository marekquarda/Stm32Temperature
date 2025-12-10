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

// position COM for segments in order ABCDEFGH (see "segment map")
const uint8_t com_key[8] = {3,2,1,0,1,3,2,0};

// position cipher (digits) in LCD RAM (see "segment map")
const uint32_t digit_segment[6][2] = {
    {1<<14,1<<15},
	{1<<24,1<<0},
	{1<<28,1<<29},
	{1<<30,1<<31},
	{1<<7, 1<<8 },
	{1<<9, 1<<16}
};

// znakovÃ¡ sada
const uint8_t charset[12]={
 // segmenty: HGFEDCBA
 0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111,	// 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b00000000,  // blank
	0b01000000  // znamenko minus
};

uint8_t disp[6]={0,0,0,0,0,0}; // "defaultnÃ­" hodnota na displeji ("0.00")
uint8_t i;