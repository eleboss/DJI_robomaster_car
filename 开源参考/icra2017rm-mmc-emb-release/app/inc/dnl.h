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
 
#ifndef __DNL_H__
#define __DNL_H__

/*****************************************/
/*        Down-Link Communication        */
/*****************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "ios.h"
#include "msg.h"
#include "cal.h"
#include "dci.h"
#include "cci.h"
#include "fun.h"
	
#define DNL_BUF_SIZE 256u
	
void Dnl_Init(void);
void Dnl_Proc(void);

/*
extern KylinMsg_t kylinMsg;
extern SubscMsg_t subscMsg;
extern VirtualDBUS_t vdbus;
extern VirtualCBUS_t vcbus;
extern CalibMsg_t calibMsg;

extern PIDCalib_t pidCalib;
extern IMUCalib_t imuCalib;
extern MagCalib_t magCalib;
extern VelCalib_t velCalib;
extern MecCalib_t mecCalib;
extern PosCalib_t posCalib;
*/

#ifdef __cplusplus
}
#endif

#endif
