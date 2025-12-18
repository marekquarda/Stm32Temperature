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

void SPI_Read(uint8_t *data, uint32_t length) {
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

void W25X_Read(uint32_t startPage, uint8_t offset, uint16_t size, uint8_t *rData) {
    uint8_t tData[5];
    uint32_t memAddr = startPage*256 + offset;
    if (numBLOCK < 512) {
        tData[0] = READ_DATA;               // Enable Read data
        tData[1] = (memAddr>>16)&0xFF;      // MSB of the memory Address
        tData[2] = (memAddr>>8)&0xFF;
        tData[3] = (memAddr)&0xFF;          // LSB of the memory Address    
    } else {
        tData[0] = READ_DATA;               // Enable Read data
        tData[1] = (memAddr>>24)&0xFF;      // MSB of the memory Address
        tData[2] = (memAddr>>16)&0xFF;
        tData[3] = (memAddr>>8)&0xFF;       
        tData[4] = (memAddr)&0xFF;          // LSB of the memory Address    
    }
    
    csLOW();
    if(numBLOCK < 512) {
        SPI_Write(tData, 4);
    } else {
        SPI_Write(tData, 5);
    }
    SPI_Read(rData, size);
    csHIGH();
}


void W25X_ReadFast(uint32_t startPage, uint8_t offset, uint16_t size, uint8_t *rData) {
    uint8_t tData[6];
    uint32_t memAddr = startPage*256 + offset;
    if (numBLOCK < 512) {
        tData[0] = FAST_READ;               // Enable Fast Read
        tData[1] = (memAddr>>16)&0xFF;      // MSB of the memory Address
        tData[2] = (memAddr>>8)&0xFF;
        tData[3] = (memAddr)&0xFF;          // LSB of the memory Address    
        tData[4] = 0;                       // Dummy clock
    } else {
        tData[0] = FAST_READ;               // Enable Fast Read
        tData[1] = (memAddr>>24)&0xFF;      // MSB of the memory Address
        tData[2] = (memAddr>>16)&0xFF;
        tData[3] = (memAddr>>8)&0xFF;       
        tData[4] = (memAddr)&0xFF;          // LSB of the memory Address   
        tData[5] = 0;                       // Dummy clock
    }
    
    csLOW();
    if(numBLOCK < 512) {
        SPI_Write(tData, 5);
    } else {
        SPI_Write(tData, 6);
    }
    SPI_Read(rData, size);
    csHIGH();
}
