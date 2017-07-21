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
 
#include "mecanum.h"

/*******************************************/
/* Mecanum Wheel Power Transmission System */
/*******************************************/
/*              2        1                 */
/*                  |y                     */
/*                 b|___x                  */
/*               z    a                    */
/*              3        4                 */
/*                                         */
/*******************************************/

void Mecanum_Config(Mecanum_t* mecanum, float lx, float ly, float r1, float r2)
{
	mecanum->l = lx + ly;
	mecanum->r = r1 + r2;

	mecanum->cx = mecanum->r / 4.0f; // mecanum->cx = r1 / 4.0f;
	mecanum->cy = mecanum->r / 4.0f; // mecanum->cy = r2 / 4.0f;
	mecanum->cz = mecanum->r / 4.0f / mecanum->l;
}

void Mecanum_Synthe(const Mecanum_t* mecanum, const float* w, float* v)
{
	v[0] = ( w[0] + w[1] - w[2] - w[3]) * mecanum->cx;
	v[1] = (-w[0] + w[1] + w[2] - w[3]) * mecanum->cy;
	v[2] = ( w[0] + w[1] + w[2] + w[3]) * mecanum->cz;
}

void Mecanum_Decomp(const Mecanum_t* mecanum, const float* v, float* w)
{
	w[0] = ( v[0] - v[1] + v[2] * mecanum->l) / mecanum->r;
	w[1] = ( v[0] + v[1] + v[2] * mecanum->l) / mecanum->r;
	w[2] = (-v[0] + v[1] + v[2] * mecanum->l) / mecanum->r;
	w[3] = (-v[0] - v[1] + v[2] * mecanum->l) / mecanum->r;
}

