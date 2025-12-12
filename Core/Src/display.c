#include "display.h"

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
uint32_t Display_Zero[2] = {
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


void display(LCD_HandleTypeDef handle, uint32_t* symbols) {
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER0, 0x00000000, symbols[0]);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER2, 0x00000000, symbols[1]);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER4, 0x00000000, symbols[2]);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER6, 0x00000000, symbols[3]);

	HAL_LCD_UpdateDisplayRequest(&handle); 
}

void show(LCD_HandleTypeDef handle) {
	clearDisp(symbols_mem);

	// display zero
	getSymbol(NUMBER_1, POSITION_0, NULL, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	// display one
	clearDisp(symbols_mem);
	getSymbol(NUMBER_0, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_1, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_2, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_3, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_4, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_5, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_6, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_7, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_8, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_9, POSITION_1, Display_One, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);

	// Display two
	clearDisp(symbols_mem);
	getSymbol(NUMBER_0, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_1, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_2, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_3, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_4, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_5, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_6, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_7, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_8, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_9, POSITION_2, Display_Two, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);

	// display three
	clearDisp(symbols_mem);
	getSymbol(NUMBER_0, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_1, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_2, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_3, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_4, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_5, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_6, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_7, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_8, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);
	getSymbol(NUMBER_9, POSITION_3, Display_Three, symbols_mem);
	display(handle, symbols_mem);
	HAL_Delay(200);
	clearDisp(symbols_mem);

	// display all numbers
	getSymbol(NUMBER_1, POSITION_0, NULL, symbols_mem);
	getSymbol(NUMBER_8, POSITION_1, Display_One, symbols_mem);
	getSymbol(NUMBER_8, POSITION_2, Display_Two, symbols_mem);
	getSymbol(NUMBER_8, POSITION_3, Display_Three, symbols_mem);
	// symbols_mem[3] |= COM3_NUMBER_1_DOT;
	// symbols_mem[3] |= COM3_NUMBER_2_DOT;
	display(handle, symbols_mem);
	// Symbols Con0 
	for (int i = 0; i < 8; ++i) {
		symbols_mem[0] |= SymbolsCom0[i];
		display(handle, symbols_mem);
		HAL_Delay(200);
	}

	// Symbols Con0 
	for (int j = 0; j < 8; ++j) {
		symbols_mem[1] |= SymbolsCom1[j];
		display(handle, symbols_mem);
		HAL_Delay(200);
	}

	for (int k = 0; k < 8; ++k) {
		symbols_mem[2] |= SymbolsCom2[k];
		display(handle, symbols_mem);
		HAL_Delay(200);
	}

	for (int l = 0; l < 9; ++l) {
		symbols_mem[3] |= SymbolsCom3[l];
		display(handle, symbols_mem);
		HAL_Delay(200);
	}

	while(1){
	//	HAL_Delay(1000);
		// if(TIM_GetFlagStatus(TIM7,TIM_FLAG_Update) != RESET){ // pokud pÅ™etekl timer
		// 	TIM_ClearFlag(TIM7,TIM_FLAG_Update); // vyÄistÃ­me vlajku
			//display(handle,0,disp); // "zobrazÃ­me" hodnoty na displeji (pÅ™epÃ­Å¡eme obsah LCD RAM)
		// }

	}
}

void clearDisp(uint32_t* symbols) {
	for(int i = 0; i <= 3; ++i) {
		symbols[i] = 0;
	}
}

void getSymbol(Number number, Position pos, int* numset, uint32_t* button) {
	switch (pos)
	{
	case POSITION_0:
		getZero(number, numset, button);
		break;
	default: // Position 1,2,3
		getNumber(number, numset, button);
		break;
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

void getZero(Number number, int* numset, uint32_t* value) {
	switch (number)
	{
	case NUMBER_1:
		value[0] = COM0_NUMBER_ONE;
		break;
	default:
		break;
	}
}

