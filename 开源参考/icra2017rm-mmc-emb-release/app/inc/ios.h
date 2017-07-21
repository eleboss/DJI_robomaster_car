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

#ifndef __IOS_H__
#define __IOS_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>

#include "tty.h"
#include "dbi.h"
#include "btm.h"
#include "fun.h"
#include "wdg.h"

#define IOS_DBG_DEV dbi
#define IOS_COM_DEV tty

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int c)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int c, FILE* f)
#define GETCHAR_PROTOTYPE int fgetc(FILE* f)
#endif

/**
 * @brief Set input streamer
 * @param in Input streamer
 * @return None
 */
void Ios_SetIn(int (*in)(void));

/**
 * @brief Set output streamer
 * @param out Output streamer
 * @return None
 */
void Ios_SetOut(int (*out)(uint8_t));

/**
 * @brief Put a character to the output stream.
 * @param c Character
 * @return None
 */
int Ios_PutCh(uint8_t c);

/**
 * @brief Get a character from the input stream.
 * @return Character
 */
int Ios_GetCh(void);

/**
 * @brief Read one byte from input stream
 * @return Read data, -1 if not available
 */
int Ios_ReadByte(void);

/**
 * @brief Write one byte to output stream
 * @return Written data count, -1 if not available
 */
int Ios_WriteByte(uint8_t data);

/**
 * @brief Read buffer from input stream fifo
 * @param buf Data buffer
 * @param len Data buffer length
 * @return Read data length, -1 if not available
 */
int Ios_Read(uint8_t* buf, uint32_t len);

/**
 * @brief Write buffer to output stream fifo
 * @param buf Data buffer
 * @param len Data buffer length
 * @return Written data length, -1 if not available
 */
int Ios_Write(const uint8_t* buf, uint32_t len);

/**
 * @brief Initialize input/output stream
 * @return None
 */
void Ios_Init(void);

#ifdef __cplusplus
}
#endif

#endif

