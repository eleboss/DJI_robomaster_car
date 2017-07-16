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

#include "flash.h"

static u32 Flash_GetSector(u32 addr)
{
	if (addr < FLASH_SECTOR_1_ADDR) {
		return FLASH_Sector_0;
	} else if (addr < FLASH_SECTOR_2_ADDR) {
		return FLASH_Sector_1;
	} else if (addr < FLASH_SECTOR_3_ADDR) {
		return FLASH_Sector_2;
	} else if (addr < FLASH_SECTOR_4_ADDR) {
		return FLASH_Sector_3;
	} else if (addr < FLASH_SECTOR_5_ADDR) {
		return FLASH_Sector_4;
	} else if (addr < FLASH_SECTOR_6_ADDR) {
		return FLASH_Sector_5;
	} else if (addr < FLASH_SECTOR_7_ADDR) {
		return FLASH_Sector_6;
	} else if (addr < FLASH_SECTOR_8_ADDR) {
		return FLASH_Sector_7;
	} else if (addr < FLASH_SECTOR_9_ADDR) {
		return FLASH_Sector_8;
	} else if (addr < FLASH_SECTOR_10_ADDR) {
		return FLASH_Sector_9;
	} else if (addr < FLASH_SECTOR_11_ADDR) {
		return FLASH_Sector_10;
	} else {
		return FLASH_Sector_11;
	}
}

static u8 Flash_ReadByte(u32 addr)
{
	return *(vu8*)addr;
}

void Flash_Read(u32 addr, u8 *buf, u32 size)
{
	u32 i = 0;
	for (; i < size; i++) {
		buf[i] = Flash_ReadByte(addr++);
	}
}

u8 Flash_Write(u32 addr, u8 *buf, u32 size)
{
	#define BREAK_IF_NOT_COMPLETE(status) if(status != FLASH_COMPLETE) break

	// flash status
	FLASH_Status status = FLASH_COMPLETE;
	// end address
	u32 end_addr = addr + size;
	// start sector
	u32 start_sector = Flash_GetSector(addr);
	// end sector
	u32 end_sector = Flash_GetSector(end_addr);

	// validate flash address
	if(addr < STM32_FLASH_BASE_ADDR) return 0;

	// unlock flash
	FLASH_Unlock();
	// disable data cache
  FLASH_DataCacheCmd(DISABLE);

  // erase sector before written
	if(addr < 0x1FFF0000)
	{
		int i = 0;
		for(i = start_sector; i <= end_sector; i += 8)
		{
			status = FLASH_EraseSector(i, VoltageRange_3);
			BREAK_IF_NOT_COMPLETE(status);
		}
	}

	// program flash byte by byte
	if(status == FLASH_COMPLETE)
	{
		while(addr < end_addr)
		{
			status = FLASH_ProgramByte(addr++, *buf++);
			BREAK_IF_NOT_COMPLETE(status);
		}
	}

	// enable data cache
	FLASH_DataCacheCmd(ENABLE);
	// lock flash
	FLASH_Lock();

	return status == FLASH_COMPLETE;
} 




