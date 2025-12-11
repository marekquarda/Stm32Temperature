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
 *        AF: SEG1 SEG2 SEG22 SEG23 SEG5 SEG8 SEG12 SEG13 SEG14 SEG15 SEG24 SEG25 SEG26 SEG27
 * PIN(disp):  5    6     7     8    9   10    11    12    13    14    15   16     17   18
 *      COM0: 5D    --    6D     T4   1D  --    --    2D   COL1   3D    --    4D    DOT1
 *      COM1: 5E    5C    6E     T3   1E  1C    6C    2E    2C    3E    3C    4E    4C
 *      COM2: 5G    5B    6G     T2   1G  1B    6B    2G    2B    3G    3B    4G    4B
 *      COM3: 5F    5A    6F     T1   1F  1A    6A    2F    2A    3F    3A    4F    4A
 *
 *      SUMMARY:
 *      digit 1: SEG1 + SEG2
 *      digit 2: SEG22 + SE23
 *      digit 3: SEG5 + SEG8
 *      digit 4: SEG12 + SEG13
 *      digit 5: SEG14  + SE15
 *      sigit 6: SEG24  + SEG25
 *         col1: SEG26
 *         dot1: SEG27
 *      battery: SEG13
 */
// position COM for segments in order ABCDEFGH (see "segment map")
const uint8_t com_key[8] = {3,2,1,0,1,3,2,0};

// position cipher (digits) in LCD RAM (see "segment map")
const uint32_t digit_segment[7][2] = {
    {1<<1,1<<2},
	{1<<22,1<<23},
	{1<<5,1<<8},
	{1<<12,1<<13},
	{1<<14, 1<<15},
	{1<<24, 1<<25},
	{1<<25, 1<<26}
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

void display(LCD_HandleTypeDef handle, uint8_t symbol, uint8_t* char_array) {
    uint32_t com[4]={0,0,0,0}; // budoucÃ­ obsah RAM LCD driveru
	uint8_t charmask,i=0,j;

	// tento blok se prostÄ› nedÃ¡ okomentovat :D jde o to pÅ™epsat "segment map" do RAM
	for(j=0;j<7;j++){ // pro kaÅ¾dou ÄÃ­slici
		charmask=charset[char_array[j]];
		for(i=0;i<3;i++){
			if(charmask & 1<<i){
				com[com_key[i]] |= digit_segment[j][1];
			}
		}

		for(i=3;i<8;i++){
			if(charmask & 1<<i){
				com[com_key[i]] |= digit_segment[j][0];
			}
		}
	}

	if(symbol & BAT_0){com[3] |= 1<<13;} // symbol "obalu baterie" T1 (na COM3 SEG13)
	if(symbol & BAT_1){com[0] |= 1<<13;} // "jedna ÄÃ¡rka" T4
	if(symbol & BAT_2){com[1] |= 1<<13;} // "druhÃ¡ ÄÃ¡rka" T3
	if(symbol & BAT_3){com[2] |= 1<<13;} // "tÅ™etÃ­ ÄÃ¡rka"	T2
	if(symbol & DOT){com[0] |= 1<<31;} // desetinnÃ¡ teÄka
	if(symbol & COLON){com[0] |= 1<<0;} // dvojteÄka

	// jestli se jeÅ¡tÄ› nestihl dokonÄit poslednÃ­ zÃ¡pis do LCD RAM tak poÄkej
	//while(HAL_LCD_GetState(LCD_FLAG_UDR) != HAL_LCD_ERROR_UDR){};
	//write to RAM
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER0, 0xF00F0066, com[0]);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER2, 0xF00F0066, com[1]);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER4, 0xF00F0066, com[2]);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER6, 0xF00F0066, com[3]);

	HAL_LCD_Write(&handle, LCD_RAM_REGISTER0, 0x00000000, 0x0FC0F066);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER2, 0x00000000, 0x0FC0F066);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER4, 0x00000000, 0x0FC0F066);
	HAL_LCD_Write(&handle, LCD_RAM_REGISTER6, 0x00000000, 0x05C0B062);

	HAL_LCD_UpdateDisplayRequest(&handle); 

	// HAL_Delay(1000);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER0, 0x00000006, 0x0000FFFF);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER2, 0x0F00F066, 0x0000FFFF);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER4, 0x0F00F066, 0x0000FFFF);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER6, 0x0F00F066, 0x0000FFFF);

	// // Update the LCD display 
	// HAL_LCD_UpdateDisplayRequest(&handle); 

	// HAL_Delay(1000);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER0, 0x0F00F066, 0xFFFF0000);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER2, 0x0F00F066, 0xFFFF0000);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER4, 0x0F00F066, 0xFFFF0000);
	// HAL_LCD_Write(&handle, LCD_RAM_REGISTER6, 0x0F00F066, 0xFFFF0000);
	// HAL_LCD_UpdateDisplayRequest(&handle); 
}

void show(LCD_HandleTypeDef handle) {
	//display(handle,0,disp); // "shows" default content of display

	while(1){
	//	HAL_Delay(1000);
		// if(TIM_GetFlagStatus(TIM7,TIM_FLAG_Update) != RESET){ // pokud pÅ™etekl timer
		// 	TIM_ClearFlag(TIM7,TIM_FLAG_Update); // vyÄistÃ­me vlajku
			// inkrementujeme poÄÃ­tadlo na displeji
			disp[5]++; // trocha matematiky ve stylu "jedna jde dÃ¡l"
			if(disp[5]>9){disp[5]=0;disp[4]++;}
			if(disp[4]>9){disp[4]=0;disp[3]++;}
			if(disp[3]>9){disp[3]=0;disp[2]++;}
			if(disp[2]>9){disp[2]=0;disp[1]++;}
			if(disp[1]>9){disp[1]=0;disp[0]++;}
			if(disp[0]>9){
				for(i=0;i<6;i++){disp[i]=0;} // napoÄÃ­tali jsme 999999s (to se vÃ¡m asi nestane)
			}
			display(handle,0,disp); // "zobrazÃ­me" hodnoty na displeji (pÅ™epÃ­Å¡eme obsah LCD RAM)
		// }
	}
}

