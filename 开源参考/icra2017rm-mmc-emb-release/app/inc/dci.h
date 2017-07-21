/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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

#ifndef __DCI_H__
#define __DCI_H__

/*****************************************/
/*        DBUS Control Interface         */
/*****************************************/

#include "dbus.h"
#include "rci.h"
#include "hci.h"
#include "wdg.h"
#include "cal.h"

void Dci_Init(void);
void Dci_Proc(const DBUS_t* dbus);

void Rcv_Proc(const uint8_t* buf);

extern DBUS_t dbus;

#endif
