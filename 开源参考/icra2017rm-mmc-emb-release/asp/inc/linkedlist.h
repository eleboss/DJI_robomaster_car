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
 
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "linkednode.h"

typedef struct LinkedList_t
{
	uint32_t size;
	struct LinkedNode_t* head;
	struct LinkedNode_t* tail;
}LinkedList_t;

LinkedList_t* LinkedList_Create(void);
uint8_t LinkedList_Add(LinkedList_t* list, void* item);
uint8_t LinkedList_Insert(LinkedList_t* list, uint32_t index, void* item);
void* LinkedList_Get(LinkedList_t* list, uint32_t index);
void* LinkedList_Set(LinkedList_t* list, uint32_t index, void* item);
void* LinkedList_Remove(LinkedList_t* list, uint32_t index);
int LinkedList_IndexOf(LinkedList_t* list, void* item);
int LinkedList_LastIndexOf(LinkedList_t* list, void* item);
uint32_t LinkedList_Size(const LinkedList_t* list);
LinkedList_t* LinkedList_SubList(LinkedList_t* list, uint32_t fromIndex, uint32_t toIndex);
void LinkedList_Destroy(LinkedList_t* list);

#ifdef __cplusplus
}
#endif

#endif
