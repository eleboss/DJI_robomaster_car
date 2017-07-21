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
 
#ifndef __ODO_H__
#define __ODO_H__

/**********************************************/
/*                  Odometer                  */
/**********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "sys.h"
#include "bsp.h"
#include "can.h"
#include "mec.h"

typedef struct
{
	PeriphsState_t fs;
	MecanumState_t mp;
	MecanumState_t mv;
	MecanumState_t mc;
	ChassisState_t cp;
	ChassisState_t cv;
	GrabberState_t gp;
	GrabberState_t gv;
	GrabberState_t gc;
}Odo_t;

void Odo_Init(void);
void Odo_Proc(void);
void Odo_Zero(void);

extern Odo_t odo;

#ifdef __cplusplus
}
#endif

#endif
