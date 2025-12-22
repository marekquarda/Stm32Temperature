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
    uint32_t memAddr = (startPage*256) + offset;
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
        tData[0] = FAST_READ_4BYTE;         // Enable Fast Read with 4-Byte Address
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

void write_enable(void) {
    uint8_t tData = WRITE_ENABLE;
    csLOW();
    SPI_Write(&tData, 1);
    csHIGH();
    W25X_Delay(5);
}


void write_disable(void) {
    uint8_t tData = WRITE_DISABLE;
    csLOW();
    SPI_Write(&tData, 1);
    csHIGH();
    W25X_Delay(5);
}

uint32_t bytesToWrite(uint32_t size, uint16_t offset) {
    if((size+offset)< 256) return size;
    else return 256-offset;
}

uint32_t bytesToModify(uint32_t size, uint16_t offset) {
    if((size+offset)< 4096) return size;
    else return 4096-offset;
}


void W25X_EraseSector(uint16_t numsector) {
    uint8_t tData[6];
    uint32_t memAddr = numsector*16*256;
    write_enable();
        if (numBLOCK < 512) {
        tData[0] = SECTOR_ERASE;            // Erase sector
        tData[1] = (memAddr>>16)&0xFF;      // MSB of the memory Address
        tData[2] = (memAddr>>8)&0xFF;
        tData[3] = (memAddr)&0xFF;           // LSB of the memory Address   
        
        csLOW();
        SPI_Write(tData, 4);
        csHIGH();
    } else {
        tData[0] = SECTOR_ERASE_4BYTE;      // Erase sector with 4-byte Address
        tData[1] = (memAddr>>24)&0xFF;      // MSB of the memory Address
        tData[2] = (memAddr>>16)&0xFF;
        tData[3] = (memAddr>>8)&0xFF;       
        tData[4] = (memAddr)&0xFF;          // LSB of the memory Address   

        csLOW();
        SPI_Write(tData, 5);
        csHIGH();
    }

    W25X_Delay(450);                        // 450ms delay for sector erase

    write_disable();
}

void W25X_WriteClean(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data) {
    uint8_t tData[266];
    uint32_t startPage = page;
    uint32_t endPage = startPage + ((size+offset-1)/256);
    uint32_t numPages = endPage-startPage+1;

    // erase sector
    uint16_t startSector = startPage/16; 
    uint16_t endSector = endPage/16;
    uint16_t numSectors = endSector-startSector+1;
    for (uint16_t i = 0; i < numSectors; i++) {
        W25X_EraseSector(startSector++);
    }

    uint32_t dataPosition = 0;

    // write the data
    for (uint32_t i = 0; i <numPages; i++) {
        uint32_t memAddr = (startPage*256)+offset;
        uint16_t bytesremaining = bytesToWrite(size, offset);
        uint32_t indx = 0;

        write_enable();

        if (numBLOCK < 512) {
            tData[0] = PAGE_PROGRAM;            // Page program
            tData[1] = (memAddr>>16)&0xFF;      // MSB of the memory Address
            tData[2] = (memAddr>>8)&0xFF;
            tData[3] = (memAddr)&0xFF;           // LSB of the memory Address   

            indx = 4;
        
        } else {
            tData[0] = PAGE_PROGRAM_4BYTE;      // Page program with 4-byte address
            tData[1] = (memAddr>>24)&0xFF;      // MSB of the memory Address
            tData[2] = (memAddr>>16)&0xFF;
            tData[3] = (memAddr>>8)&0xFF;       
            tData[4] = (memAddr)&0xFF;          // LSB of the memory Address   

            indx = 5;
        }

        uint16_t bytestosend = bytesremaining + indx;

        for (uint16_t i = 0; i < bytesremaining; i++)
        {
            tData[indx++] = data[i+dataPosition];
        }

        if (bytestosend > 250) {
            csLOW();
            SPI_Write(tData, 100);
            SPI_Write(tData+100, bytestosend-100);
            csHIGH();
            
        } else {
            csLOW();
            SPI_Write(tData, bytestosend);
            csHIGH();
        }

        startPage++;
        offset = 0;
        size = size-bytesremaining;
        dataPosition = dataPosition+bytesremaining;

        W25X_Delay(5);
        write_disable();
    }
}

void W25X_Write(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data) {
    // erase sector
    uint16_t startSector = page/16; 
    uint16_t endSector = (page + ((size+offset-1)/256))/16;
    uint16_t numSectors = endSector-startSector+1;

    uint8_t prevousData[4096];
    uint32_t sectorOffset = ((page%16)*256)+offset;
    uint32_t dataindx = 0;

    for (uint16_t i = 0; i < numSectors; i++) {
        uint32_t startPage = startSector*16;
        W25X_ReadFast(startPage, 0, 4096, prevousData);

        uint16_t bytesRemaining = bytesToModify(size, sectorOffset);
        for(uint16_t j = 0; j < bytesRemaining; j++) {
            prevousData[j+sectorOffset] = data[j+dataindx];
        }

        W25X_WriteClean(startPage, 0, 4096, prevousData);

        startSector++;
        sectorOffset = 0;
        dataindx = dataindx+bytesRemaining;
        size = size-bytesRemaining;
    }
}

uint8_t W25X_ReadByte(uint32_t Addr) {
    uint8_t tData[5];
    uint8_t rData;

    if (numBLOCK < 512) {
        tData[0] = READ_DATA;            // Enable Read data
        tData[1] = (Addr>>16)&0xFF;      // MSB of the memory Address
        tData[2] = (Addr>>8)&0xFF;
        tData[3] = (Addr)&0xFF;          // LSB of the memory Address    
    } else {
        tData[0] = READ_DATA_4BYTE;      // Enable Read Data with 4-Byte Address
        tData[1] = (Addr>>24)&0xFF;      // MSB of the memory Address
        tData[2] = (Addr>>16)&0xFF;
        tData[3] = (Addr>>8)&0xFF;       
        tData[4] = (Addr)&0xFF;          // LSB of the memory Address    
    }
    
    csLOW(); 
    if(numBLOCK < 512) {
        SPI_Write(tData, 4);
    } else {
        SPI_Write(tData, 5);
    }
    SPI_Read(&rData, 1);
    csHIGH();

    return rData;
}

void W25X_WriteByte(uint32_t Addr, uint8_t data) {
    uint8_t tData[6];
    uint8_t indx;

    if (numBLOCK < 512) {
        tData[0] = PAGE_PROGRAM;         // Page Program
        tData[1] = (Addr>>16)&0xFF;      // MSB of the memory Address
        tData[2] = (Addr>>8)&0xFF;
        tData[3] = (Addr)&0xFF;          // LSB of the memory Address    
        tData[4] = data;
        indx = 5;
    } else {
        tData[0] = PAGE_PROGRAM_4BYTE;   // Page Program with 4-Byte Address
        tData[1] = (Addr>>24)&0xFF;      // MSB of the memory Address
        tData[2] = (Addr>>16)&0xFF;
        tData[3] = (Addr>>8)&0xFF;       
        tData[4] = (Addr)&0xFF;          // LSB of the memory Address    
        tData[5] = data;
        indx = 6;
    }

    if (W25X_ReadByte(Addr) == 0xFF) {
        write_enable();
        csLOW();
        SPI_Write(tData, indx);
        csHIGH();

        W25X_Delay(5);
        write_disable();
    }
}

void float2Bytes(uint8_t * ftoa_bytes_temp, float float_variable) {
    union {
        float a;
        uint8_t bytes[4];
    } thing;
    
    thing.a = float_variable;
    for (uint8_t i = 0; i < 4; i++) {
        ftoa_bytes_temp[i] = thing.bytes[i];
    }
}

uint8_t tempBytes[4];

float Bytes2float(uint8_t * ftoa_bytes_temp) {
    union  {
        float a;
        uint8_t bytes[4];
    } think;
    
    for (uint8_t i = 0; i < 4; i++) {
        think.bytes[i] = ftoa_bytes_temp[i];
    }

    float float_variable = think.a;
    return float_variable;
}

void W25X_WriteNUM(uint32_t page, uint16_t offset, float data) {
    float2Bytes(tempBytes, data);

    /* write using single byte function */
    uint32_t Addr = (page*256)+offset;
    for (int i = 0; i < 4; i++) {
        W25X_WriteByte(i+Addr, tempBytes[i]);
    }

    /* Write using sector update function */
    // W25X_Write([page, offset, 4, tempBytes]);
}

float W25X_ReadNUM(uint32_t page, uint16_t offset) {
    uint8_t rData[4];
    W25X_Read(page, offset, 4, rData);
    
    return (Bytes2float(rData));
}

void W25X_Write32B(uint32_t page, uint16_t offset, uint32_t size, uint32_t *data) {
    uint8_t data8[size*4];
    uint32_t indx = 0;

    for (uint32_t i = 0; i < size; i++) {
        data8[indx++] = data[i]*0xFF;   // extract LSB
        data8[indx++] = (data[i]>>8)&0xFF;
        data8[indx++] = (data[i]>>16)&0xFF;
        data8[indx++] = (data[i]>>24)&0xFF;
    }

    W25X_Write(page, offset, indx, data8);
}

void W25X_Read32B(uint32_t page, uint16_t offset, uint32_t size, uint32_t *data) {
    uint8_t data8[size*4];
    uint32_t indx = 0;

    W25X_ReadFast(page, offset, size*4, data8);

    for (uint32_t i = 0; i < size; i++) {
        data[i] = (data8[indx++]) | (data8[indx++]<<8) | (data8[indx++]<<16) | (data8[indx++]<<24);
    }
}
