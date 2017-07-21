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

#include "app.h"

/**************************************/
/*            Application             */
/**************************************/

void App_Init(void)
{
	Ios_Init(); // Input/output stream initialization
	Cfg_Init(); // Configuration initialization
	Clk_Init(); // Clock initialization
	Mec_Init(); // Mechanical parameters initialization
	Can_Init(); // Can bus initialization
	Odo_Init(); // Odometry initialization
	Cmd_Init(); // Command initialization
	Ctl_Init(); // Logic controller initialization
	Upl_Init(); // Up-link communication initialization
	Dnl_Init(); // Down-link communication initialization
	Com_Init(); // Communication initialization
	Dci_Init(); // DBUS control interface initialization
	Cal_Init(); // Calibration initialization
	Pwr_Init(); // Power manager initialization
	Srs_Init(); // SR04 sonar system initialization
	Snd_Init(); // Sound initialization
	
	Wdg_Init(); // Watch dog initialization
	Ini_Init(); // Sensor prefilter information provider initialization
	Wsm_Init(); // Work state machine initialization
	Upd_Init(); // System updater initialization
}

void App_Proc(void)
{
	Wdg_Proc();
	Ini_Proc();
	Wsm_Proc();
	Upd_Proc();
}


