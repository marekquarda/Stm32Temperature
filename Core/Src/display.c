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
uint32_t button0[3][1];
uint32_t button1[3][7];
uint32_t button2[3][7];
uint32_t button3[3][6]; 

// character sets (com, number)
// segment HGFEDCBA
const uint8_t charset[12] = {
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
	0b00000000, // blank
	0b01000000  // minus
};

uint32_t Display_Zero[1] = {
    COM0_NUMBER_ONE,
    COM1_NUMBER_ONE_DOT
};

const int Display_One[7] = {
    COM0_NUMBER_1A,
    COM1_NUMBER_1B, 
    COM2_NUMBER_1C, 
    COM3_NUMBER_1D, 
    COM0_NUMBER_1E, 
    COM1_NUMBER_1F,
    COM2_NUMBER_1G, 
    COM3_NUMBER_1_DOT
};

int Display_Two[7] = {
    COM0_NUMBER_2A,
    COM1_NUMBER_2B, 
    COM2_NUMBER_2C, 
    COM3_NUMBER_2D, 
    COM0_NUMBER_2E, 
    COM1_NUMBER_2F,
    COM2_NUMBER_2G, 
    COM3_NUMBER_2_DOT
};

int Display_Three[6] = {
    COM0_NUMBER_3A,
    COM1_NUMBER_3B, 
    COM2_NUMBER_3C, 
    COM3_NUMBER_3D, 
    COM0_NUMBER_3E, 
    COM1_NUMBER_3F,
    COM2_NUMBER_3G 
};


void display(LCD_HandleTypeDef handle, uint32_t* symbols) {
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER0, 0x00000000, symbols[0]);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER2, 0x00000000, symbols[1]);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER4, 0x00000000, symbols[2]);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER6, 0x00000000, symbols[3]);

	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER0, 0x00000000, 0x0FC0F066);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER2, 0x00000000, 0x0FC0F066);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER4, 0x00000000, 0x0FC0F066);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER6, 0x00000000, 0x05C0B062);

	HAL_LCD_UpdateDisplayRequest(&handle); 
}

void show(LCD_HandleTypeDef handle) {
	clearDisp(symbols_mem);
	//display(handle,0,disp); // "shows" default content of display
    //addSymbol(COM0, COM0_SYMBOL_HEART, symbols_mem);
	display(handle, symbols_mem);
	getSymbol(NUMBER_1, POSITION_0, NULL, button0);
	display(handle, button0);
	//getSymbol(NUMBER_1, POSITION_0, button0);
	while(1){
	//	HAL_Delay(1000);
		// if(TIM_GetFlagStatus(TIM7,TIM_FLAG_Update) != RESET){ // pokud pÅ™etekl timer
		// 	TIM_ClearFlag(TIM7,TIM_FLAG_Update); // vyÄistÃ­me vlajku
			//display(handle,0,disp); // "zobrazÃ­me" hodnoty na displeji (pÅ™epÃ­Å¡eme obsah LCD RAM)
		// }

	}
}

// void addSymbol(Coms com, uint32_t value, uint32_t *symbols) {
// 	switch (com)
// 	{
// 	case COM0:
// 		symbols[0] = value;
// 		break;
// 	case COM1:
// 		symbols[1] = value;
// 		break;
// 	case COM2:
// 		symbols[2] = value;
// 		break;		
// 	case COM3:
// 		symbols[3] = value;
// 		break;		
// 	default:
// 		break;
// 	}
// }

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
	case POSITION_1:
		getNumber(number, numset, button);
		break;
	case POSITION_2:
		getNumber(number, numset, button);
		break;
	case POSITION_3:
		getNumber(number,numset, button);
		break;
	default:
		return NULL;
	}
}

uint32_t* getNumber(Number number, int* numset, uint32_t* value) {
	switch (number)
	{
	case NUMBER_0:
		/* code */
		break;
	case NUMBER_1:
		
		break;
	case NUMBER_2:
			
		break;							
	case NUMBER_3:
			
		break;
	case NUMBER_4:
		
		break;
	case NUMBER_5:
			
		break;
	case NUMBER_6:
			
		break;							
	case NUMBER_7:
			
		break;
	case NUMBER_8:
			
		break;
	case NUMBER_9:

		break;
	case NUMBER_BLANK:

		break;		
	case NUMBER_DASH:

		break;
	default:
		break;
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

