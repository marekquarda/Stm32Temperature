#include "display.h"
#include "clock.h"
#include "usbd_cdc.h"

/* Displej TempTale Ultra
 *
 * Common map:
 * disp(pin)  stm32(pin)
 * COM1(17)   COM3 (PB9)
 * COM2(16)   COM2 (PA10)
 * COM3(15)   COM1 (PA9)
 * COM4(14)   COM0 (PA8)
 *
 * segment map (relation with STM32):
 *  PIN(stm): PA2  PA3   PC4   PC5  PB0  PB1  PB12  PB13  PB14  PB15  PC6   PC7   PC8   PC9
 *        AF: SEG1 SEG2 SEG22 SEG23 SEG5 SEG6 SEG12 SEG13 SEG14 SEG15 SEG24 SEG25 SEG26 SEG27
 * PIN(disp):  14    13    12    11   10   9    8     7     6     5     4     3     2     1
 *
 */

uint32_t symbols_mem[3];
uint8_t sendBuffer[128];
LCD_HandleTypeDef lcd;
RTC_DateTypeDef sDate;
RTC_TimeTypeDef sTime;
uint8_t hour[2], minutes[2], seconds[2];
uint8_t day[2], month[2], year[2], week[2];

int Display_Zero[2] = {
    COM0_NUMBER_ONE,
    COM1_NUMBER_ONE_DOT
};

int Display_One[8] = {
    COM0_NUMBER_1A,
    COM1_NUMBER_1B, 
    COM2_NUMBER_1C, 
    COM3_NUMBER_1D, 
    COM0_NUMBER_1E, 
    COM1_NUMBER_1F,
    COM2_NUMBER_1G, 
    COM3_NUMBER_1_DOT
};

int Display_Two[8] = {
    COM0_NUMBER_2A,
    COM1_NUMBER_2B, 
    COM2_NUMBER_2C, 
    COM3_NUMBER_2D, 
    COM0_NUMBER_2E, 
    COM1_NUMBER_2F,
    COM2_NUMBER_2G, 
    COM3_NUMBER_2_DOT
};

int Display_Three[7] = {
    COM0_NUMBER_3A,
    COM1_NUMBER_3B, 
    COM2_NUMBER_3C, 
    COM3_NUMBER_3D, 
    COM0_NUMBER_3E, 
    COM1_NUMBER_3F,
    COM2_NUMBER_3G 
};

uint32_t SymbolsCom0[7] = {
	COM0_SYMBOL_LIGHT,             
 	COM0_SYMBOL_HEART,
	COM0_SYMBOL_ARROW_UP,
	COM0_SYMBOL_LINE_DOWN,
	COM0_SYMBOL_TRIANGLE_UP,
	COM0_SYMBOL_BASE_DEGREE,
	COM0_SYMBOL_PERCENTAGE
};

uint32_t SymbolsCom1[7] = {
	COM1_SYMBOL_PROBE,
	COM1_SYMBOL_DASH,
	COM1_SYMBOL_TEMP,
	COM1_SYMBOL_DLINE_DOWN,
	COM1_SYMBOL_TRIANGLE_DOWN,
	COM1_SYMBOL_DEGREE_FAHR,
	COM1_SYMBOL_RH
};

uint32_t SymbolsCom2[7] = {
	COM2_SYMBOL_GARBLE_TIME,
	COM2_SYMBOL_BATTERY,     
	COM2_SYMBOL_DAY_S,       
	COM2_SYMBOL_DLINE_UP,    
	COM2_SYMBOL_HEXAGON_FULL,
	COM2_SYMBOL_DEGREE_CELS,
	COM2_SYMBOL_HR_S
};

uint32_t SymbolsCom3[8] = {
	COM3_SYMBOL_NONE_1,       
	COM3_SYMBOL_TIME,         
	COM3_SYMBOL_NONE_2,       
	COM3_SYMBOL_AVG,          
	COM3_SYMBOL_MIN,          
	COM3_SYMBOL_MAX,          
	COM3_SYMBOL_NONE_4,       
	COM3_SYMBOL_MIN_S        
};

void initDisplay(LCD_HandleTypeDef handle) {
	lcd = handle;
}

void showTime() {
	clearDisp(symbols_mem);
	getFormatTime(sTime, hour, minutes, seconds);
	//logComPort(TIME, hour, minutes, seconds, NULL);
	getFormatDate(sDate, day, month, year, week);
	logComPort(DAY, day, month, year, week);
	getSymbol(getNumberEnum(seconds[0]),POSITION_3, symbols_mem);
	getSymbol(getNumberEnum(seconds[1]),POSITION_2, symbols_mem);
	display(symbols_mem);
	
}

void logComPort(DayOrTime daytime, uint8_t* first, uint8_t* second, uint8_t* third, uint8_t* four) {
	switch (daytime)
	{
	case DAY:
		snprintf((char*) sendBuffer, sizeof(sendBuffer), "Day: %01d%01d.%01d%01d.%01d%01d, Week: %01d%01d\n\r", first[1], first[0], second[1], second[0], third[1], third[0], four[1], four[0]);
    	CDC_Transmit_FS(sendBuffer, sizeof(sendBuffer));
		break;
	case TIME:
		snprintf((char*) sendBuffer, sizeof(sendBuffer), "Time: %01d%01d:%01d%01d:%01d%01d\n\r", first[1], first[0], second[1], second[0], third[1], third[0]);
    	CDC_Transmit_FS(sendBuffer, sizeof(sendBuffer));
		break;
	default:
		break;
	}
	
}

void reloadDisplay(RTC_DateTypeDef myDate, RTC_TimeTypeDef myTime) {
	sDate = myDate;
	sTime = myTime;
	showTime();
}

void display(uint32_t* symbols) {
	HAL_LCD_Write(&lcd, LCD_RAM_REGISTER0, 0x00000000, symbols[0]);
	HAL_LCD_Write(&lcd, LCD_RAM_REGISTER2, 0x00000000, symbols[1]);
	HAL_LCD_Write(&lcd, LCD_RAM_REGISTER4, 0x00000000, symbols[2]);
	HAL_LCD_Write(&lcd, LCD_RAM_REGISTER6, 0x00000000, symbols[3]);

	HAL_LCD_UpdateDisplayRequest(&lcd); 
}

void testLcd() {
	clearDisp(symbols_mem);

	while(1){
	}
}

void clearDisp(uint32_t* symbols) {
	for(int i = 0; i <= 3; ++i) {
		symbols[i] = 0;
	}
}

void getSymbol(Number number, Position pos, uint32_t* value) {
	switch (pos)
	{
	case POSITION_0:
		getZero(number, Display_Zero, value);
		break;
	case POSITION_1:
		getNumber(number, Display_One, value);
		break;		
	case POSITION_2:
		getNumber(number, Display_Two, value);
		break;		
	case POSITION_3:
		getNumber(number, Display_Three, value);
		break;		
	default: // Position 1,2,3
		break;
	}
}

Number getNumberEnum(uint8_t number) {
	switch (number)
	{
	case 1:
		return NUMBER_1;
	case 2:
		return NUMBER_2;
	case 3:
		return NUMBER_3;
	case 4:
		return NUMBER_4;
	case 5:
		return NUMBER_5;
	case 6:
		return NUMBER_6;
	case 7:
		return NUMBER_7;
	case 8:
		return NUMBER_8;
	case 9:
		return NUMBER_9;
	case 0:
		return NUMBER_0;
	}
}

void getNumber(Number number, int* numset, uint32_t* value) {
	int temp = number;
	for (int i = 0; i < 8; ++i) {
		//temp = number & 0x01;
		if ((temp & 0x1) > 0) {
			if (i <= 3) {
				value[i] |= numset[i];
			} else {
				value[i-4] |= numset[i];
			}
		}
		temp = temp >> 1;
	}
}

void getZero(Number number, int* numset, u_int32_t* value) {
	switch (number)
	{
	case NUMBER_1:
		value[0] = COM0_NUMBER_ONE;
		break;
	default:
		break;
	}
}

