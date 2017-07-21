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
 
#ifndef __HCI_H__
#define __HCI_H__

/********************************************/
/*          Host Control Interface          */
/********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "hcf.h"
#include "maf.h"
#include "cmd.h"

#define HCI_KEY_CTL_MAF_LEN 10

void Hci_Init(void);
void Hci_Proc(const Hcp_t* hcp);

void Hci_PreProc(const Hcp_t* hcp); // Called by Hci_Proc, should not call in other location
uint8_t Hci_MouseBtn(uint8_t i);

#ifdef __cplusplus
}
#endif

#endif
