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
 
#include "linkednode.h"

LinkedNode_t* LinkedNode_Create(void* item)
{
	LinkedNode_t* node = (LinkedNode_t*)malloc(sizeof(LinkedNode_t));
	if (node == NULL) {
		return NULL;
	}
	memset(node, 0, sizeof(LinkedNode_t));
	node->item = item;
	return node;
}

LinkedNode_t* LinkedNode_SearchForward(LinkedNode_t* node, uint32_t index)
{
	LinkedNode_t* curr = node;
	int i = -1;
	for (; curr != NULL; curr = curr->next) {
		if (++i == index) {
			return curr;
		}
	}
	return NULL;
}

LinkedNode_t* LinkedNode_SearchBackward(LinkedNode_t* node, uint32_t index)
{
	LinkedNode_t* curr = node;
	int i = -1;
	for (; curr != NULL; curr = curr->prev) {
		if (++i == index) {
			return curr;
		}
	}
	return NULL;
}

LinkedNode_t* LinkedNode_SearchFirstForward(LinkedNode_t* node, void* item)
{
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->next) {
		if (curr->item == item) {
			return curr;
		}
	}
	return NULL;
}

LinkedNode_t* LinkedNode_SearchFirstBackward(LinkedNode_t* node, void* item)
{
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->prev) {
		if (curr->item == item) {
			return curr;
		}
	}
	return NULL;
}

LinkedNode_t* LinkedNode_SearchLastForward(LinkedNode_t* node, void* item)
{
	LinkedNode_t* last = NULL;
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->next) {
		if (curr->item == item) {
			last = curr;
		}
	}
	return last;
}

LinkedNode_t* LinkedNode_SearchLastBackward(LinkedNode_t* node, void* item)
{
	LinkedNode_t* last = NULL;
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->prev) {
		if (curr->item == item) {
			last = curr;
		}
	}
	return last;
}

LinkedNode_t* LinkedNode_AddBefore(LinkedNode_t* node, void* item)
{
	if (node != NULL) {
		LinkedNode_t* newNode = LinkedNode_Create(item);
		if (newNode == NULL) {
			return NULL;
		}
		if (node->prev != NULL) {
			newNode->prev = node->prev;
			node->prev->next = newNode;
		}
		node->prev = newNode;
		newNode->next = node;
		return newNode;
	}
	return NULL;
}

LinkedNode_t* LinkedNode_AddAfter(LinkedNode_t* node, void* item)
{
	if (node != NULL) {
		LinkedNode_t* newNode = LinkedNode_Create(item);
		if (newNode == NULL) {
			return NULL;
		}
		if (node->next != NULL) {
			newNode->next = node->next;
			node->next->prev = newNode;
		}
		newNode->prev = node;
		node->next = newNode;
		return newNode;
	}
	return NULL;
}

void* LinkedNode_SetItem(LinkedNode_t* node, void* newItem)
{
	if (node != NULL) {
		void* oldItem = node->item;
		node->item = newItem;
		return oldItem;
	}
	return NULL;
}

void* LinkedNode_Remove(LinkedNode_t* node)
{
	if (node != NULL) {
		void* item = node->item;
		if (node->prev != NULL) {
			node->prev->next = node->next;
		}
		if (node->next != NULL) {
			node->next->prev = node->prev;
		}
		free(node);
		return item;
	}
	return NULL;
}

int LinkedNode_FirstIndexForward(LinkedNode_t* node, void* item)
{
	int index = -1;
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->next) {
		++index;
		if (curr->item == item) {
			return index;
		}
	}
	return -1;
}

int LinkedNode_FirstIndexBackward(LinkedNode_t* node, void* item)
{
	int index = -1;
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->prev) {
		++index;
		if (curr->item == item) {
			return index;
		}
	}
	return -1;
}

int LinkedNode_LastIndexForward(LinkedNode_t* node, void* item)
{
	int index = -1;
	int temp = -1;
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->next) {
		++temp;
		if (curr->item == item) {
			index = temp;
		}
	}
	return index;
}

int LinkedNode_LastIndexBackward(LinkedNode_t* node, void* item)
{
	int index = -1;
	int temp = -1;
	LinkedNode_t* curr = node;
	for (; curr != NULL; curr = curr->prev) {
		++temp;
		if (curr->item == item) {
			index = temp;
		}
	}
	return index;
}

int LinkedNode_SizeForward(LinkedNode_t* node)
{
	int size = -1;
	for (; node != NULL; node = node->next) {
		++size;
	}
	return size;
}

int LinkedNode_SizeBackward(LinkedNode_t* node)
{
	int size = -1;
	for (; node != NULL; node = node->prev) {
		++size;
	}
	return size;
}




