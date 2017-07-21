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
 
#ifndef __DBG_H__
#define __DBG_H__

/*************************************/
/*       Debug Function Calls        */
/*************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define DBUG 0

#if DBUG

#include "ios.h"
#include "com.h"
#include "cfg.h"
#include "wsm.h"
#include "ctl.h"
#include "srs.h"
	
void Dbg_Cfg(void);
void Dbg_Mec(void);
void Dbg_Cvl(void);
void Dbg_Gvl(void);
void Dbg_Gpl(void);
void Dbg_Rci(void);
void Dbg_Hci(void);
void Dbg_Dci(void);
void Dbg_Cmd(void);
void Dbg_Odo(void);
void Dbg_Wsm(void);
void Dbg_Wdg(void);
void Dbg_Can(void);
void Dbg_Ecd(void);
void Dbg_Vrc(void);
void Dbg_Vhc(void);
void Dbg_Vdc(void);
void Dbg_Vcc(void);
void Dbg_Imu(void);
void Dbg_Ctl(void);
void Dbg_Srs(void);

#endif

#ifdef __cplusplus
}
#endif

#endif


