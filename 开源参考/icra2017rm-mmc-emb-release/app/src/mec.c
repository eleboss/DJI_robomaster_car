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

#include "mec.h"

/*******************************************/
/*     Coordinate Transforming System      */
/* Mecanum Wheel Power Transmission System */
/*******************************************/
/*              2        1                 */
/*                  |y                     */
/*                 b|___x                  */
/*               z    a                    */
/*              3        4                 */
/*                                         */
/*******************************************/

static Mecanum_t mecanum;

void Mec_Config(float lx, float ly, float r1, float r2)
{
	Mecanum_Config(&mecanum, lx, ly, r1, r2);
}

void Mec_Synthe(const float* w, float* v)
{
	Mecanum_Synthe(&mecanum, w, v);
}

void Mec_Decomp(const float* v, float* w)
{
	Mecanum_Decomp(&mecanum, v, w);
}

void Mec_Init(void)
{
	Mecanum_Config(&mecanum, cfg.mec.lx, cfg.mec.ly, cfg.mec.r1, cfg.mec.r2);
}


