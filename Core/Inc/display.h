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

// uint32_t Display_Zero[1] = {
//     COM0_NUMBER_ONE,
//     COM1_NUMBER_ONE_DOT
// };

// const int Display_One[8] = {
//     COM0_NUMBER_1A,
//     COM1_NUMBER_1B, 
//     COM2_NUMBER_1C, 
//     COM3_NUMBER_1D, 
//     COM0_NUMBER_1E, 
//     COM1_NUMBER_1F,
//     COM2_NUMBER_1G, 
//     COM3_NUMBER_1_DOT
// };

// int Display_Two[7] = {
//     COM0_NUMBER_2A,
//     COM1_NUMBER_2B, 
//     COM2_NUMBER_2C, 
//     COM3_NUMBER_2D, 
//     COM0_NUMBER_2E, 
//     COM1_NUMBER_2F,
//     COM2_NUMBER_2G, 
//     COM3_NUMBER_2_DOT
// };

// int Display_Three[6] = {
//     COM0_NUMBER_3A,
//     COM1_NUMBER_3B, 
//     COM2_NUMBER_3C, 
//     COM3_NUMBER_3D, 
//     COM0_NUMBER_3E, 
//     COM1_NUMBER_3F,
//     COM2_NUMBER_3G 
// };

typedef enum {
    COM0,
    COM1,
    COM2,
    COM3
} Coms;

// typedef enum {
//     NUMBER_1A = COM0_NUMBER_1A,
//     NUMBER_1B = COM1_NUMBER_1B,
//     NUMBER_1C = COM2_NUMBER_1C,
//     NUMBER_1D = COM3_NUMBER_1D,
//     NUMBER_1E = COM0_NUMBER_1E,
//     NUMBER_1F = COM1_NUMBER_1F,
//     NUMBER_1G = COM2_NUMBER_1G,
// } Position_one;

// typedef enum {
//     NUMBER_2A = COM0_NUMBER_2A,
//     NUMBER_2B = COM1_NUMBER_2B,
//     NUMBER_2C = COM2_NUMBER_2C,
//     NUMBER_2D = COM3_NUMBER_2D,
//     NUMBER_2E = COM0_NUMBER_2E,
//     NUMBER_2F = COM1_NUMBER_2F,
//     NUMBER_2G = COM2_NUMBER_2G,
// } Position_two;

// typedef enum {
//     NUMBER_3A = COM0_NUMBER_3A,
//     NUMBER_3B = COM1_NUMBER_3B,
//     NUMBER_3C = COM2_NUMBER_3C,
//     NUMBER_3D = COM3_NUMBER_3D,
//     NUMBER_3E = COM0_NUMBER_3E,
//     NUMBER_3F = COM1_NUMBER_3F,
//     NUMBER_3G = COM2_NUMBER_3G,
// } Position_three;

typedef enum {
    NUMBER_0,
    NUMBER_1,
    NUMBER_2,                       
    NUMBER_3, 
    NUMBER_4,                        
    NUMBER_5,                        
    NUMBER_6,                        
    NUMBER_7,
    NUMBER_8,                        
    NUMBER_9,                        
    NUMBER_BLANK,
    NUMBER_DASH
} Number;

typedef enum {
    POSITION_0,
    POSITION_1,
    POSITION_2,
    POSITION_3
} Position;


void display(LCD_HandleTypeDef handle, uint32_t *symbols);
void clearDisp(uint32_t* symbols);
void getSymbol(Number number, Position pos, int* numset, uint32_t *button);
void getZero(Number number, int* numset, uint32_t* value);
uint32_t* getNumber(Number number, int* numset, uint32_t* value);
//void addSymbol(Coms com, uint32_t value, uint32_t *symbols);
void show(LCD_HandleTypeDef handle);

#endif