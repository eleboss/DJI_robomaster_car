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
 
#ifndef __LINKEDNODE_H__
#define __LINKEDNODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedNode_t
{
	void* item;
	struct LinkedNode_t* prev;
	struct LinkedNode_t* next;
}LinkedNode_t;

LinkedNode_t* LinkedNode_Create(void* item);

LinkedNode_t* LinkedNode_SearchForward(LinkedNode_t* node, uint32_t index);
LinkedNode_t* LinkedNode_SearchBackward(LinkedNode_t* node, uint32_t index);
LinkedNode_t* LinkedNode_SearchFirstForward(LinkedNode_t* node, void* item);
LinkedNode_t* LinkedNode_SearchFirstBackward(LinkedNode_t* node, void* item);
LinkedNode_t* LinkedNode_SearchLastForward(LinkedNode_t* node, void* item);
LinkedNode_t* LinkedNode_SearchLastBackward(LinkedNode_t* node, void* item);

LinkedNode_t* LinkedNode_AddBefore(LinkedNode_t* node, void* item);
LinkedNode_t* LinkedNode_AddAfter(LinkedNode_t* node, void* item);

void* LinkedNode_Remove(LinkedNode_t* node);

void* LinkedNode_SetItem(LinkedNode_t* node, void* newItem);

int LinkedNode_FirstIndexForward(LinkedNode_t* node, void* item);
int LinkedNode_FirstIndexBackward(LinkedNode_t* node, void* item);
int LinkedNode_LastIndexForward(LinkedNode_t* node, void* item);
int LinkedNode_LastIndexBackward(LinkedNode_t* node, void* item);
int LinkedNode_SizeForward(LinkedNode_t* node);
int LinkedNode_SizeBackward(LinkedNode_t* node);

#ifdef __cplusplus
}
#endif

#endif
