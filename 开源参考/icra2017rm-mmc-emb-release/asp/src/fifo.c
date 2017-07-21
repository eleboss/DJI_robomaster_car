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
 
#include "fifo.h"

void FIFO_Init(FIFO_t* fifo, uint8_t* m, uint32_t s)
{
	fifo->m = m;
	fifo->s = s;
	FIFO_Flush(fifo);
}

void FIFO_Flush(FIFO_t* fifo)
{
	memset(fifo->m, 0, fifo->s * sizeof(uint8_t));
	fifo->r = 0;
	fifo->w = 0;
	fifo->n = 0;
}

uint32_t FIFO_Push(FIFO_t* fifo, const uint8_t* e, uint32_t n)
{
	uint32_t i = 0;
	for (; i < n && fifo->n != fifo->s; i++, fifo->n++) {
		fifo->m[fifo->w++] = e[i];
		if (fifo->w == fifo->s) fifo->w = 0;
	}
	return i;
}

uint32_t FIFO_Pop(FIFO_t* fifo, uint8_t* e, uint32_t n)
{
	uint32_t i = 0;
	for (; i < n && fifo->n != 0; i++, fifo->n--) {
		e[i] = fifo->m[fifo->r++];
		if (fifo->r == fifo->s) fifo->r = 0;
	}
	return i;
}

uint32_t FIFO_Peek(const FIFO_t* fifo, uint8_t* e, uint32_t n)
{
	uint32_t i = 0, j = fifo->r;
	for (; i < n && i < fifo->n; i++) {
		e[i] = fifo->m[j++];
		if (j == fifo->s) j = 0;
	}
	return i;
}

uint8_t FIFO_IsFull(const FIFO_t* fifo)
{
	return fifo->n == fifo->s;
}

uint8_t FIFO_IsEmpty(const FIFO_t* fifo)
{
	return fifo->n == 0;
}

uint32_t FIFO_GetSize(const FIFO_t* fifo)
{
	return fifo->s;
}

uint32_t FIFO_GetUsed(const FIFO_t* fifo)
{
	return fifo->n;
}

uint32_t FIFO_GetFree(const FIFO_t* fifo)
{
	return fifo->s - fifo->n;
}

FIFO_t* FIFO_Create(uint32_t s)
{
	FIFO_t* fifo = (FIFO_t*)malloc(sizeof(FIFO_t));
	if (fifo == NULL) return NULL;
	memset(fifo, 0, sizeof(FIFO_t));
	fifo->s = s;
	fifo->m = (uint8_t*)malloc(s * sizeof(uint8_t));
	if (fifo->m == NULL)
	{
		free(fifo);
		fifo = NULL;
		return NULL;
	}
	FIFO_Flush(fifo);
	return fifo;
}

void FIFO_Destroy(FIFO_t* fifo)
{
	if (fifo != NULL) {
		if (fifo->m != NULL) {
			free(fifo->m);
			fifo->m = NULL;
		}
		free(fifo);
		fifo = NULL;
	}
}

