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

#include "ios.h"

int (*_in)(void); // Input stream pipe
int (*_out)(uint8_t); // Output stream pipe

/**
 * @brief Set input stream pipe.
 * @param in Input stream pipe.
 * @return None.
 */
void Ios_SetIn(int (*in)(void))
{
	if (in) _in = in;
}

/**
 * @brief Set output stream pipe.
 * @param in Output stream pipe.
 * @return None.
 */
void Ios_SetOut(int (*out)(uint8_t))
{
	if (out) _out = out;
}

/**
 * @brief Put a character to the output stream.
 * @param c Character
 * @return None
 */
int Ios_PutCh(uint8_t c)
{
	Dbi_PutCh(c);
	Btm_PutCh(c);
	return c;
}

/**
 * @brief Get a character from the input stream.
 * @return Character
 */
int Ios_GetCh(void)
{
	return Dbi_GetCh();
}

/**
 * @brief Stdio stream write function implementation.
 */
PUTCHAR_PROTOTYPE
{
	if (_out) { 
		return _out(c);
	} else {
		return -1;
	}
}

/**
 * @brief Stdio stream read function implementation.
 */
GETCHAR_PROTOTYPE
{
	if (_in) {
		return _in();
	} else {
		return -1;
	}
}

/**
 * @brief Read a single byte from the input stream.
 * @param None.
 * @return A single byte.
 */
int Ios_ReadByte(void)
{
	// Priority: TTY > DBI > BTM
	if (Tty_GetRxFifoUsed() > 0) {
		return Tty_ReadByte();
	} else if (Dbi_GetRxFifoUsed() > 0) {
		return Dbi_ReadByte();
	} else if (Btm_GetRxFifoUsed() > 0) {
		return Btm_ReadByte();
	}
	return -1;
}

/**
 * @brief Write a single byte to the output stream.
 * @param data Byte data.
 * @return None
 */
int Ios_WriteByte(uint8_t data)
{
	// Priority: TTY > DBI > BTM
	//while (Tty_GetTxFifoFree() < 1);
	//return Tty_WriteByte(data);
	while (Dbi_GetTxFifoFree() < 1);
	return Dbi_WriteByte(data);
	
	/*
	if (Tty_GetTxFifoFree() > 0) {
		return Tty_WriteByte(data);
	} else if (Dbi_GetTxFifoFree() > 0) {
		return Dbi_WriteByte(data);
	} else if (Btm_GetTxFifoFree() > 0) {
		return Btm_WriteByte(data);
	}
	return -1;
	*/
	//USART_TypeDef* USART = TTY_USART;
	//while (USART_GetFlagStatus(USART, USART_FLAG_TC) == RESET);
	//USART->DR = data;
	//return data;
}

/**
 * @brief Read input stream buffer.
 * @param buf Stream buffer
 * @param len Stream length
 * @return Stream length
 */
int Ios_Read(uint8_t* buf, uint32_t len)
{
	// Priority: TTY > DBI > BTM
	/*
	if (Tty_GetRxFifoUsed() > 0) {
		return Tty_Read(buf, len);
	} else if (Dbi_GetRxFifoUsed() > 0) {
		return Dbi_Read(buf, len);
	} else if (Btm_GetRxFifoUsed() > 0) {
		return Btm_Read(buf, len);
	}
	return -1;
	*/
	return Dbi_Read(buf, len);
}

/**
 * @brief Write output stream buffer.
 * @param buf Stream buffer
 * @param len Stream length
 * @return Stream length
 */
int Ios_Write(const uint8_t* buf, uint32_t len)
{
	// Priority: TTY > DBI > BTM
	if (Tty_GetTxFifoFree() > 0) {
		return Tty_Write(buf, len);
	} else if (Dbi_GetTxFifoFree() > 0) {
		return Dbi_Write(buf, len);
	} else if (Btm_GetTxFifoFree() > 0) {
		return Btm_Write(buf, len);
	}
	return -1;
}

/**
 * @brief Initialize the input/output stream pipe to default.
 * @return None
 */
void Ios_Init(void)
{
	Ios_SetIn(Ios_GetCh);
	Ios_SetOut(Ios_PutCh);
}


