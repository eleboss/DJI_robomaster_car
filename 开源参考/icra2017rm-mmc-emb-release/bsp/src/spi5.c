/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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
 
#include "spi5.h"

void Spi5_Config(void)
{
	GPIO_Out(SPI5_NSS_PIN);
	SPI_Bind(0,
	         SPI5_SCK_PIN,
	         SPI5_MISO_PIN,
	         SPI5_MOSI_PIN,
	         SPI5,
	         SPI_Mode_Master,
	         SPI_Direction_2Lines_FullDuplex,
	         SPI_DataSize_8b,
	         SPI_CPOL_Low,
	         SPI_CPHA_1Edge,
	         SPI_NSS_Soft,
	         SPI_BaudRatePrescaler_128,
	         SPI_FirstBit_MSB,
	         10);
	
	SPI_Cmd(SPI5, ENABLE);
	
}
