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

#define numBLOCK            8       // Number of total blocks for 4Mb flash 8x16x16x256
#define JEDEC_ID            0x9F    // JEDEC ID
#define READ_DATA           0x03    // Read data
#define FAST_READ           0x0B    // Fast Read data

#define csLOW() HAL_GPIO_WritePin(GPIOA, SPI1_CS_Pin, GPIO_PIN_RESET);
#define csHIGH() HAL_GPIO_WritePin(GPIOA, SPI1_CS_Pin, GPIO_PIN_SET);

uint32_t W25X_ReadID(void);
void W25X_Read(uint32_t startPage, uint8_t offset, uint16_t size, uint8_t *rData);
void W25X_ReadFast(uint32_t startPage, uint8_t offset, uint16_t size, uint8_t *rData);
void SPI_Write(uint8_t *data, uint8_t length);
void SPI_Read(uint8_t *data, uint32_t length);


#endif