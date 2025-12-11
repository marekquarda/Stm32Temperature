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
    addSymbol(COM0, COM0_SYMBOL_HEART, symbols_mem);
	display(handle, symbols_mem);
	while(1){
	//	HAL_Delay(1000);
		// if(TIM_GetFlagStatus(TIM7,TIM_FLAG_Update) != RESET){ // pokud pÅ™etekl timer
		// 	TIM_ClearFlag(TIM7,TIM_FLAG_Update); // vyÄistÃ­me vlajku
			//display(handle,0,disp); // "zobrazÃ­me" hodnoty na displeji (pÅ™epÃ­Å¡eme obsah LCD RAM)
		// }

	}
}

void addSymbol(Coms com, uint32_t value, uint32_t *symbols) {
	switch (com)
	{
	case COM0:
		symbols[0] = value;
		break;
	case COM1:
		symbols[1] = value;
		break;
	case COM2:
		symbols[2] = value;
		break;		
	case COM3:
		symbols[3] = value;
		break;		
	default:
		break;
	}
}

void clearDisp(uint32_t* symbols) {
	for(int i = 0; i <= 3; ++i) {
		symbols[i] = 0;
	}
}

// int* showNumber(Position position, Number number, uint32_t* symbols[3]) {
// 	int* temp[3];

// 	switch (position)
// 	{
// 	case POSITION_0:
// 		switch (number) 
// 		{
// 		case NUMBER_0:
			
// 			break;
// 		case NUMBER_1:
			
// 			break;
// 		case NUMBER_2:
			
// 			break;							

// 		case NUMBER_3:
			
// 			break;
// 		case NUMBER_4:
			
// 			break;
// 		case NUMBER_5:
			
// 			break;
// 		case NUMBER_6:
			
// 			break;							
// 		case NUMBER_7:
			
// 			break;
// 		case NUMBER_8:
			
// 			break;
// 		case NUMBER_9:
			
// 			break;
// 		default:
// 			break;
// 		}
// 		break;
// 	case POSITION_1:

// 		break;

// 	case POSITION_2:
	
// 		break;

// 	case POSITION_3:
	
// 		break;
// 	default:
// 		break;
// 	}
// 	return &temp;
// }

