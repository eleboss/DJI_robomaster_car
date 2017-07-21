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
 
#include "kos.h"

/**********************************************/
/*           Kylin Operating System           */
/**********************************************/

void KOS_Boot(void)
{
	// Application initialization
	App_Init();
	
	// Scheduler initialization 
	Sch_Init();
	
	// Arrange scheduled tasks, @{SYS_CTL_TMS} ms/exec
//	Sch_Arrange(App_Proc, SYS_CTL_TMS);
//	Sch_Arrange(Snd_Proc, SND_PLAY_TMS / 2);
//	Sch_Arrange(Srs_Proc, SRS_TRIG_TMS / 2);
//	Sch_Arrange(Pwr_Proc, PWR_SAMPLE_TMS); // Power manager disabled
	
	// BSP configuration
	Bsp_Config();
	
	// Action initialization
	Act_Init();
	
	// Start timer
	Tim_Start();
}

void KOS_Stop(void)
{
	// Dismiss application process
	Sch_Dismiss(App_Proc);
	Sch_Dismiss(Snd_Proc);
	//Sch_Dismiss(Pwr_Proc);
	
	//Reset all active peripherals
	Act_Init();
}


