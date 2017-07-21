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

#ifndef __FUN_H__
#define __FUN_H__

/******************************************************/
/*                  Helper Functions                  */
/******************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// commonly used macros
#define PI 3.1415926f
#define DEG2RAD_RECIP 7.669904e-4f
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)
#define MIN(V1,V2) (V1<V2?V1:V2)
#define MAX(V1,V2) (V1>V2?V1:V2)
#define LIMIT_MAX(V,M) do { if (V > M) V = M; } while (0)
#define LIMIT_MIN(V,M) do { if (V < M) V = M; } while (0)
#define LIMIT(X,MIN,MAX) do { X = X > MAX ? MAX : X < MIN ? MIN : X; } while(0)
#define LIMIT_ABS(V,M) LIMIT(V,-M,M)
#define ABSVAL(V) ( (V) < 0 ? (-V) : (V) )

typedef uint32_t Flag_t;

float min(float v1, float v2);
float max(float v1, float v2);
float map(float val, float min1, float max1, float min2, float max2);
float constrain(float val, float min, float max);

Flag_t Flag_Get(const Flag_t* flag, Flag_t mask);
Flag_t Flag_Hit(const Flag_t* flag, Flag_t mask);
void Flag_Set(Flag_t* flag, Flag_t mask);
void Flag_Clr(Flag_t* flag, Flag_t mask);
void Flag_Tog(Flag_t* flag, Flag_t mask);
void Flag_Cpy(Flag_t* flag, Flag_t src, Flag_t mask);
void Flag_Det(Flag_t* flag, Flag_t mask, uint32_t condition);

#ifdef __cplusplus
}
#endif

#endif
