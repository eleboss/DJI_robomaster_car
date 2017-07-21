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
 
#ifndef __RCI_H__
#define __RCI_H__

/**********************************************/
/*          Remote Control Interface          */
/**********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "rcf.h"
#include "cmd.h"

void Rci_Init(void);
void Rci_Proc(const Rcp_t* rcp);

void Rci_PreProc(const Rcp_t* rcp);
uint8_t Rci_Sw(uint8_t i);
uint8_t Rci_LastSw(uint8_t i);

#ifdef __cplusplus
}
#endif

#endif
