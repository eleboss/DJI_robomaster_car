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

#include "sch.h"

/********************************************************/
/*                    Task Scheduler                    */
/********************************************************/

static uint32_t tick = 0;

static SchTask_t* first = NULL;
static SchTask_t* last = NULL;

void Sch_Init(void)
{
	tick = 0;
	SchTask_t* curr = first;
	for (; curr != NULL; curr = curr->next) {
		curr->lastrun = 0;
	}
}

void Sch_Proc(void)
{
	//uint32_t tick = Clk_GetMsTick();
	SchTask_t* curr = first;
	tick++;
	for (; curr != NULL; curr = curr->next) {
		uint32_t interval = tick - curr->lastrun;
		//uint32_t interval = tick > curr->lastrun ? tick - curr->lastrun : (uint32_t)0xFFFFFFFF - curr->lastrun + tick;
		if (interval >= curr->interval) {
			curr->run();
			curr->lastrun = tick;
		}
	}
}

static SchTask_t* newSchTask(SchRun_t run, uint32_t interval)
{
	SchTask_t* task = (SchTask_t*)malloc(sizeof(SchTask_t));
	if (task == NULL) return NULL;
	memset(task, 0, sizeof(SchTask_t));
	task->run = run;
	task->interval = interval;
	task->prev = NULL;
	task->next = NULL;
	return task;
}

static void delSchTask(SchTask_t* task)
{
	if (task == first) {
		first = task->next;
	}
	if (task == last) {
		last = task->prev;
	}
	if (task->prev != NULL) {
		task->prev->next = task->next;
	}
	if (task->next != NULL) {
		task->next->prev = task->prev;
	}
	free(task);
	task = NULL;
}

static SchTask_t* getSchTask(SchRun_t run)
{
	SchTask_t* curr = first;
	for (; curr != NULL; curr = curr->next) {
		if (curr->run == run) {
			return curr;
		}
	}
	return NULL;
}

static void addSchTask(SchTask_t* curr)
{
	last->next = curr;
	curr->prev = last;
	last = curr;
}

uint8_t Sch_Arrange(SchRun_t run, uint32_t interval)
{
	if (first == NULL) {
		first = newSchTask(run, interval);
		last = first;
		return 1;
	} else {
		SchTask_t* curr = getSchTask(run);
		if (curr != NULL) {
			curr->interval = interval;
			return 1;
		}
		else {
			curr = newSchTask(run, interval);
			addSchTask(curr);
		}
		return 0;
	}
}

uint8_t Sch_Dismiss(SchRun_t run)
{
	if (first == NULL) {
		return 0;
	}
	else {
		SchTask_t* curr = getSchTask(run);
		if (curr != NULL) {
			delSchTask(curr);
			return 1;
		}
		return 0;
	}
}
