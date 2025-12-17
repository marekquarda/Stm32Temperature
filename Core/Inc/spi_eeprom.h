/*
 * @file        spi_eeprom.h
 * @brief       SPI EEPROM Library
 * @author      Marek Quarda
 * @version     1.0.0
 */

#ifndef _SPI_EEPROM_H_
#define _SPI_EEPROM_H_

#include "main.h"

extern SPI_HandleTypeDef hspi1;
#define W25X_SPI hspi1

#define csLOW() HAL_GPIO_WritePin(GPIOA, SPI1_CS_Pin, GPIO_PIN_RESET);
#define csHIGH() HAL_GPIO_WritePin(GPIOA, SPI1_CS_Pin, GPIO_PIN_SET);

#define numBLOCK    8       // Number of total blocks for 4Mb flash
#define JEDEC_ID    0x9F    // JEDEC ID

uint32_t W25X_ReadID(void);

#endif