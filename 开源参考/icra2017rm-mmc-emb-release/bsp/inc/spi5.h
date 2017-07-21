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

#ifndef __SPI5_H__
#define __SPI5_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"

#define SPI5_NSS_PIN PF6
#define SPI5_SCK_PIN PF7
#define SPI5_MISO_PIN PF8
#define SPI5_MOSI_PIN PF9

#define SPI5_NSS_H() GPIO_SET(SPI5_NSS_PIN)
#define SPI5_NSS_L() GPIO_RST(SPI5_NSS_PIN)

#define SPI5_TXRX_BYTE(TXD,RXD,TIMEOUT) SPI_TxRxByte(SPI5,TXD,RXD,TIMEOUT)
#define SPI5_TXRX(TXD,RXD,LEN,TIMEOUT) SPI_TxRx(SPI5,TXD,RXD,LEN,TIMEOUT)
	
void Spi5_Config(void);

#ifdef __cplusplus
}
#endif

#endif


