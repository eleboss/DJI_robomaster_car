#ifndef __MPU6500_SPI_H__
#define __MPU6500_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "spi5.h"

#define MPU6500_SPI SPI5

#define MPU6500_SPI_NSS_L() SPI5_NSS_L()
#define MPU6500_SPI_NSS_H() SPI5_NSS_H()

#define MPU6500_SPI_TIMEOUT 0

#define MPU6500_SPI_TXRX_BYTE(TXD,RXD) SPI5_TXRX_BYTE(TXD,RXD,MPU6500_SPI_TIMEOUT)
#define MPU6500_SPI_TXRX(TXD,RXD,LEN) SPI5_TXRX(TXD,RXD,LEN,MPU6500_SPI_TIMEOUT)

uint8_t MPU6500_SPI_Write_Reg(uint8_t reg, uint8_t data);
uint8_t MPU6500_SPI_Read_Reg(uint8_t reg, uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif
