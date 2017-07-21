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

#ifndef __STACK_H__
#define __STACK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	uint8_t* buf;
	uint32_t size;
	uint32_t p;
}Stack_t;

void Stack_Init(Stack_t* stack, uint8_t* buf, uint32_t size);
void Stack_Dump(Stack_t* stack);
uint32_t Stack_Push(Stack_t* stack, const uint8_t* elements, uint32_t size);
uint32_t Stack_Pop(Stack_t* stack, uint8_t* elements, uint32_t size);
uint32_t Stack_Peek(const Stack_t* stack, uint8_t* elements, uint32_t size);
uint8_t Stack_IsFull(const Stack_t* stack);
uint8_t Stack_IsEmpty(const Stack_t* stack);
uint8_t Stack_GetSize(const Stack_t* stack);
uint32_t Stack_GetUsed(const Stack_t* stack);
uint32_t Stack_GetFree(const Stack_t* stack);

Stack_t* Stack_Create(uint32_t size);
void Stack_Destroy(Stack_t* stack);

#ifdef __cplusplus
}
#endif

#endif

