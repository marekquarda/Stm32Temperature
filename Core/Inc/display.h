#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "main.h"
#include "stm32l1xx_hal_lcd.h"

// macro for argument "symbol" in function display(), their combinations takes symbols for viewing
// COM0 symbols
#define COM0_SYMBOL_LIGHT               0x8000000
#define COM0_SYMBOL_HEART               0x4000000
#define COM0_NUMBER_ONE                 0x2000000
#define COM0_NUMBER_1A                  0x1000000
#define COM0_NUMBER_1E                  0x0008000
#define COM0_SYMBOL_ARROW_UP            0x0004000
#define COM0_SYMBOL_LINE_DOWN           0x0002000
#define COM0_NUMBER_2A                  0x0001000
#define COM0_NUMBER_2E                  0x0000040
#define COM0_NUMBER_3A                  0x0000020
#define COM0_NUMBER_3E                  0x0800000
#define COM0_SYMBOL_TRIANGLE_UP         0x0400000
#define COM0_SYMBOL_BASE_DEGREE         0x0000004
#define COM0_SYMBOL_PERCENTAGE          0x0000002

// COM1 symbols
#define COM1_SYMBOL_PROBE               0x8000000
#define COM1_SYMBOL_DASH                0x4000000
#define COM1_NUMBER_ONE_DOT             0x2000000
#define COM1_NUMBER_1B                  0x1000000
#define COM1_NUMBER_1F                  0x0008000
#define COM1_SYMBOL_TEMP                0x0004000
#define COM1_SYMBOL_DLINE_DOWN          0x0002000
#define COM1_NUMBER_2B                  0x0001000
#define COM1_NUMBER_2F                  0x0000040
#define COM1_NUMBER_3B                  0x0000020
#define COM1_NUMBER_3F                  0x0800000
#define COM1_SYMBOL_TRIANGLE_DOWN       0x0400000
#define COM1_SYMBOL_DEGREE_FAHR         0x0000004
#define COM1_SYMBOL_RH                  0x0000002

// COM2 symbols
#define COM2_SYMBOL_GARBLE_TIME         0x8000000
#define COM2_SYMBOL_BATTERY             0x4000000
#define COM2_SYMBOL_DAY_S               0x2000000
#define COM2_NUMBER_1C                  0x1000000
#define COM2_NUMBER_1G                  0x0008000
#define COM2_NUMBER_COLON               0x0004000
#define COM2_SYMBOL_DLINE_UP            0x0002000
#define COM2_NUMBER_2C                  0x0001000
#define COM2_NUMBER_2G                  0x0000040
#define COM2_NUMBER_3C                  0x0000020
#define COM2_NUMBER_3G                  0x0800000
#define COM2_SYMBOL_HEXAGON_FULL        0x0400000
#define COM2_SYMBOL_DEGREE_CELS         0x0000004
#define COM2_SYMBOL_HR_S                0x0000002

// COM3 symbols
#define COM3_SYMBOL_NONE_1              0x8000000
#define COM3_SYMBOL_TIME                0x4000000
#define COM3_SYMBOL_NONE_2              0x2000000
#define COM3_NUMBER_1D                  0x1000000
#define COM3_NUMBER_1_DOT               0x0008000
#define COM3_NUMBER_NONE_3              0x0004000
#define COM3_SYMBOL_AVG                 0x0002000
#define COM3_NUMBER_2D                  0x0001000
#define COM3_NUMBER_2_DOT               0x0000040
#define COM3_NUMBER_3D                  0x0000020
#define COM3_SYMBOL_MIN                 0x0800000
#define COM3_SYMBOL_MAX                 0x0400000
#define COM3_SYMBOL_NONE_4              0x0000004
#define COM3_SYMBOL_MIN_S               0x0000002

typedef enum {
    COM0,
    COM1,
    COM2,
    COM3
} Coms;


typedef enum {
    NUMBER_0 = 0b00111111,      // 0
    NUMBER_1 = 0b00000110,      // 1
    NUMBER_2 = 0b01011011,      // 2 
    NUMBER_3 = 0b01001111,	    // 3
	NUMBER_4 = 0b01100110,      // 4
	NUMBER_5 = 0b01101101,      // 5
	NUMBER_6 = 0b01111101,      // 6
	NUMBER_7 = 0b00000111,      // 7
	NUMBER_8 = 0b01111111,      // 8
	NUMBER_9 = 0b01101111,      // 9
	NUMBER_BLANK = 0b00000000,  // blank
	NUMBER_DASH = 0b01000000,   // minus                    
    NO_SYMBOL_U = 0b00111110,   // U
    NO_SYMBOL_A = 0b01110111,   // A
    NO_SYMBOL_C = 0b00111001,   // C
    NO_SYMBOL_E = 0b01111001,   // E
    NO_SYMBOL_F = 0b01110001,   // F
    NO_SYMBOL_Y = 0b01100110,   // Y
    NO_SYMBOL_L = 0b00111000,   // L - Long
    NO_SYMBOL_S = 0b01101101,   // 5 - Short
    NO_SYMBOL_H = 0b01110110    // H
} Number;

typedef enum {
    POSITION_0,
    POSITION_1,
    POSITION_2,
    POSITION_3
} Position;

extern uint32_t symbols_mem[3];

void initDisplay(LCD_HandleTypeDef handle);
void reloadDisplay(void);
void display(uint32_t *symbols);
void clearDisp(uint32_t* symbols);
Number getNumberEnum(uint8_t number);
void getSymbol(Number number, Position pos, uint32_t *button);
void getZero(Number number, int* numset, uint32_t* value);
void getNumber(Number number, int* numset, uint32_t* value);
//
void testLcd();

#endif