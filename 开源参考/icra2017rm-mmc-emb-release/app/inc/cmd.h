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

#ifndef __CMD_H__
#define __CMD_H__

/**********************************************/
/*          System Command Interface          */
/**********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "sys.h"
#include "mec.h"
#include "cfg.h"
#include "fun.h"

typedef struct
{
	PeriphsState_t fs; // Functional state control bits reference
	ChassisState_t cv; // Chassis velocity reference
	ChassisState_t cp; // Chassis position reference
	MecanumState_t mv; // Mecanum velocity reference (Auto-Wired)
	MecanumState_t mp; // Mecanum position reference (Auto-Wired)
	GrabberState_t gv; // Grabber velocity dynamic reference
	GrabberState_t gp; // Grabber position reference
}Cmd_t;

void Cmd_Init(void);
void Cmd_Proc(void);
void Cmd_Zero(void);

extern Cmd_t cmd;

#ifdef __cplusplus
}
#endif

#endif
