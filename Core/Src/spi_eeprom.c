/*
 * @file        spi_eeprom.h
 * @brief       SPI EEPROM Library
 * @author      Marek Quarda
 * @version     1.0.0
 */

#include "spi_eeprom.h"


void SPI_Write(uint8_t *data, uint8_t length) {
    HAL_SPI_Transmit(&W25X_SPI, data, length, 2000);
};

void SPI_Read(uint8_t *data, uint8_t length) {
    HAL_SPI_Receive(&W25X_SPI, data, length, 5000);
};

uint32_t W25X_ReadID(void) 
{
    uint8_t tData = JEDEC_ID;
    uint8_t rData[3];
    csLOW();
    HAL_SPI_Transmit(&W25X_SPI, &tData, 1, 1000);
    HAL_SPI_Receive(&W25X_SPI, rData, 3, 3000);
    csHIGH();
    return ((rData[0]<< 16) | (rData[1]<< 8) | rData[2]);
}
