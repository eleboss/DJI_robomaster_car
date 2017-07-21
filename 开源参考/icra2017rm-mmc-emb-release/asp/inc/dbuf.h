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

#ifndef __DBUSF_H__
#define __DBUSF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rcf.h"
#include "hcf.h"
#include "dbus.h"
	
typedef struct
{
	Rcf_t rcf;
	Hcf_t hcf;
}DBuf_t;

void DBuf_Init(DBuf_t* dbuf);
void DBuf_Proc(DBuf_t* dbuf, const DBUS_t* dbus);

#ifdef __cplusplus
}
#endif

#endif




