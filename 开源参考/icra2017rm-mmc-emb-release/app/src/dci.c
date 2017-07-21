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

#include "dci.h"

/*****************************************/
/*        DBUS Control Interface         */
/*****************************************/

DBUS_t dbus;

void Dci_Init(void)
{
	Rci_Init();
	Hci_Init();
	DBUS_Init(&dbus);
}

void Dci_Proc(const DBUS_t* dbus)
{
	if (Cal_IsDone()) {
		Rci_PreProc(&dbus->rcp);
		if (Rci_Sw(SW_IDX_R) == SW_UP) {
			Rci_Proc(&dbus->rcp);
		} else if (Rci_Sw(SW_IDX_R) == SW_MD) {
			Hci_Proc(&dbus->hcp);
		} else if (Rci_Sw(SW_IDX_R) == SW_DN) {
			// Other control interface
		} else {
			// Should never reach here
		}
	}
}

void Rcv_Proc(const uint8_t* dbuf)
{
	Wdg_Feed(WDG_IDX_RCV);
	DBUS_Dec(&dbus, dbuf);
	Dci_Proc(&dbus);
}

