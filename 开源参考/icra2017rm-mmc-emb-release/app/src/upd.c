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
 
#include "upd.h"

/**********************************************/
/*               System Updater               */
/**********************************************/

void Upd_Init(void)
{
	memcpy(&cmd.cp, &odo.cp, sizeof(ChassisState_t));
	memcpy(&cmd.cv, &odo.cv, sizeof(ChassisState_t));
	memcpy(&cmd.gp, &odo.gp, sizeof(GrabberState_t));
	memcpy(&cmd.gv, &odo.gv, sizeof(GrabberState_t));
	memcpy(&cmd.fs, &odo.fs, sizeof(PeriphsState_t));
}

void Upd_Proc(void)
{
	switch (Wsm_GetWs()) {
		case WORKING_STATE_STOP:
			Act_Init(); // Stop any kind of movement
		  Odo_Proc(); // Odometry process
			Upd_Init(); // Initialize updater
		  Cmd_Proc(); // Command process
			break;
		case WORKING_STATE_PREPARE:
			Act_Init(); // Sensor data prefilter, stop any kind of movement
		  Odo_Proc(); // Odometry process
			Upd_Init(); // Initialize updater
		  Cmd_Proc(); // Command process
			break;
		case WORKING_STATE_CALIB:
			Odo_Proc(); // Odometer process
			Cal_Proc(); // Auto-calibration
		  Upd_Init(); // Initialize updater
		  Cmd_Proc(); // Command process
			break;
		case WORKING_STATE_NORMAL:
			if (Wsm_GetLastWs() != WORKING_STATE_NORMAL) {
				Odo_Proc(); // Odometry process
				Upd_Init(); // Initialize updater
				Cmd_Proc(); // Command process
			} else {
				Cmd_Proc(); // Command process
				Odo_Proc(); // Odometry process
				Ctl_Proc(); // Logic controller process
				Act_Proc(); // Action process
			}
			break;
		case WORKING_STATE_CONFIG:
			Act_Init(); // Stop movement before configuration
			Cfg_Proc(); // Configuration process
			Mec_Init(); // Mechanical parameters initialization
			Ctl_Init(); // Logic controller initialization
			break;
		case WORKING_STATE_OVERLOAD:
			Act_Init(); // Stop any kind of movement
		  Odo_Proc(); // Odometry process
			Upd_Init(); // Initialize updater
		  Cmd_Proc(); // Command process
			break;
		default:
			break;
	}
}




