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
 
#include "linkedlist.h"

LinkedList_t* LinkedList_Create()
{
	LinkedList_t* list = (LinkedList_t*)malloc(sizeof(LinkedList_t));
	if (list == NULL) {
		return NULL;
	}
	memset(list, 0, sizeof(LinkedList_t));
	return list;
}

uint8_t LinkedList_Add(LinkedList_t* list, void* item)
{
	if (list != NULL) {
		if (list->head == NULL) {
			list->head = LinkedNode_Create(item);
			if (list->head == NULL) {
				return 0;
			}
			list->tail = list->head;
			return 1;
		} else {
			LinkedNode_t* node = LinkedNode_AddAfter(list->tail, item);
			if (node != NULL) {
				list->tail = node;
				list->size++;
				return 1;
			}
		}
	}
	return 0;
}

uint8_t LinkedList_Insert(LinkedList_t* list, uint32_t index, void* item)
{
	if (list != NULL && index < list->size) {
		LinkedNode_t* node = LinkedNode_SearchForward(list->head, index);
		if (node != NULL) {
			LinkedNode_t* newNode = LinkedNode_AddBefore(node, item);
			if (newNode != NULL) {
				if (node == list->head) list->head = newNode;
				list->size++;
				return 1;
			}
		}
	}
	return 0;
}

void* LinkedList_Get(LinkedList_t* list, uint32_t index)
{
	if (list != NULL) {
		LinkedNode_t* node = LinkedNode_SearchForward(list->head, index);
		if (node != NULL) {
			return node->item;
		}
	}
	return NULL;
}

void* LinkedList_Set(LinkedList_t* list, uint32_t index, void* item)
{
	if (list != NULL) {
		LinkedNode_t* node = LinkedNode_SearchForward(list->head, index);
		if (node != NULL) {
			return LinkedNode_SetItem(node, item);
		}
	}
	return NULL;
}

void* LinkedList_Remove(LinkedList_t* list, uint32_t index)
{
	void* item = NULL;
	if (list != NULL) {
		LinkedNode_t* node = LinkedNode_SearchForward(list->head, index);
		if (node != NULL) {
			if (node == list->head) list->head = list->head->next;
			item = LinkedNode_Remove(node);
			list->size--;
			return item;
		}
	}
	return NULL;
}

int LinkedList_IndexOf(LinkedList_t* list, void* item)
{
	if (list != NULL) {
		return LinkedNode_FirstIndexForward(list->head, item);
	}
	return -1;
}

int LinkedList_LastIndexOf(LinkedList_t* list, void* item)
{
	int index = -1;
	if (list != NULL) {
		if ((index = LinkedNode_FirstIndexBackward(list->tail, item)) > 0) {
			return list->size - index - 1;
		}
	}
	return -1;
}

uint32_t LinkedList_Size(const LinkedList_t* list)
{
	if (list != NULL) {
		return list->size;
	}
	return 0;
}

LinkedList_t* LinkedList_SubList(LinkedList_t* list, uint32_t fromIndex, uint32_t toIndex)
{
	if (list == NULL || fromIndex >= toIndex) return NULL;
	if (list->head != NULL && list->tail != NULL) {
		uint32_t size = toIndex - fromIndex;
		if (size > list->size) return NULL;
		LinkedList_t* sublist = LinkedList_Create();
		if (sublist == NULL) {
			return NULL;
		}
		else {
			uint32_t i = 0;
			LinkedNode_t* node = LinkedNode_SearchForward(list->head, fromIndex);
			for (; i < size; i++) {
				LinkedList_Add(sublist, node->item);
				node = node->next;
			}
			sublist->size = size;
			return sublist;
		}
	}
	return NULL;
}

void LinkedList_Destroy(LinkedList_t* list)
{
	if (list != NULL) {
		LinkedNode_t* curr = list->head;
		LinkedNode_t* next = curr->next;
		while (curr != NULL) {
			next = curr->next;
			LinkedNode_Remove(curr);
			curr = next;
		}
		free(list);
	}
}

