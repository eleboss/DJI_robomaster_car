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
 
#ifndef __CCI_H__
#define __CCI_H__

/*************************************************/
/*            CBUS Control Interface             */
/*************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "cmd.h"
#include "odo.h"
#include "ctl.h"
#include "dci.h"
#include "wdg.h"
#include "wsm.h"
#include "cbus.h"

#define CCI_DPT_TH 0.3f //0.5f // Chassis translation position difference threshold
#define CCI_DPR_TH 0.1f //0.3f // Chassis rotation position difference threshold
#define CCI_DPE_TH 0.1f //0.3f // Grabber elevator position difference threshold
#define CCI_DPC_TH 1e-6f //0.3f // Grabber claw position difference threshold
	
void Cci_Init(void);
void Cci_Proc(const CBUS_t* cbus);

#ifdef __cplusplus
}
#endif

#endif

