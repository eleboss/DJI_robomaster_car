/**
 * Copyright (c) 2011-2016, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mpu6500_spi.h"

uint8_t MPU6500_SPI_Write_Reg(uint8_t reg, uint8_t data)
{
  uint8_t txData, rxData, flag;
  
  MPU6500_SPI_NSS_L();
  
  txData = reg & 0x7f;
	
	flag = MPU6500_SPI_TXRX_BYTE(txData, &rxData);

	RETURN_ZERO_IF_ASSERT_FAILED(flag);
	
  txData = data;
	
	flag = MPU6500_SPI_TXRX_BYTE(txData, &rxData);
	
	RETURN_ZERO_IF_ASSERT_FAILED(flag);
	
  MPU6500_SPI_NSS_H();
	
  return 1;
}

uint8_t MPU6500_SPI_Read_Reg(uint8_t reg, uint8_t* data)
{
  uint8_t txData, rxData, flag;
  
  MPU6500_SPI_NSS_L();
  
  txData = reg | 0x80;
	
	flag = MPU6500_SPI_TXRX_BYTE(txData, &rxData);

	RETURN_ZERO_IF_ASSERT_FAILED(flag);
	
  *data = rxData;
	
  MPU6500_SPI_NSS_H();
	
  return 1;
}

