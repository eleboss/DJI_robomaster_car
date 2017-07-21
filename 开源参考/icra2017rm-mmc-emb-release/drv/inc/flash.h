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

#ifndef __FLASH_H__
#define __FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "platform.h"

#define STM32_FLASH_BASE_ADDR 0x08000000
 
#define FLASH_SECTOR_0_ADDR     ((u32)0x08000000) 	// 16k
#define FLASH_SECTOR_1_ADDR     ((u32)0x08004000) 	// 16k
#define FLASH_SECTOR_2_ADDR     ((u32)0x08008000) 	// 16k
#define FLASH_SECTOR_3_ADDR     ((u32)0x0800C000) 	// 16k
#define FLASH_SECTOR_4_ADDR     ((u32)0x08010000) 	// 64k
#define FLASH_SECTOR_5_ADDR     ((u32)0x08020000) 	// 128k
#define FLASH_SECTOR_6_ADDR     ((u32)0x08040000) 	// 128k
#define FLASH_SECTOR_7_ADDR     ((u32)0x08060000) 	// 128k
#define FLASH_SECTOR_8_ADDR     ((u32)0x08080000) 	// 128k
#define FLASH_SECTOR_9_ADDR     ((u32)0x080A0000) 	// 128k
#define FLASH_SECTOR_10_ADDR    ((u32)0x080C0000) 	// 128k
#define FLASH_SECTOR_11_ADDR    ((u32)0x080E0000) 	// 128k

void Flash_Read(u32 addr, u8* buf, u32 size);
u8 Flash_Write(u32 addr, u8* buf, u32 size);

#ifdef __cplusplus
}
#endif

#endif




