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

#ifndef __WDG_H__
#define __WDG_H__

/***********************************/
/*            Watch Dog            */
/***********************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint32_t WdgErr_t;
	
#define WDG_NUM              22u

#define WDG_IDX_RCV          0u
#define WDG_IDX_TTY          1u
#define WDG_IDX_BTM          2u
#define WDG_IDX_DBI          3u
#define WDG_IDX_IMU          4u
#define WDG_IDX_VRC          5u
#define WDG_IDX_VHC          6u
#define WDG_IDX_VDBUS        7u
#define WDG_IDX_CBUS         8u
#define WDG_IDX_CALIB        9u
#define WDG_IDX_ZGYRO        10u
#define WDG_IDX_MOTOR1       11u
#define WDG_IDX_MOTOR2       12u
#define WDG_IDX_MOTOR3       13u
#define WDG_IDX_MOTOR4       14u
#define WDG_IDX_MOTOR5       15u
#define WDG_IDX_MOTOR6       16u
#define WDG_IDX_KYLIN        17u
#define WDG_IDX_SR04F        18u
#define WDG_IDX_SR04M        19u
#define WDG_IDX_SR04L        20u
#define WDG_IDX_SR04R        21u

#define WDG_ERR_RCV			   (1u<<WDG_IDX_RCV)
#define WDG_ERR_TTY			   (1u<<WDG_IDX_TTY)
#define WDG_ERR_BTM			   (1u<<WDG_IDX_BTM)
#define WDG_ERR_DBI			   (1u<<WDG_IDX_DBI)
#define WDG_ERR_IMU			   (1u<<WDG_IDX_IMU)
#define WDG_ERR_VRC			   (1u<<WDG_IDX_VRC)
#define WDG_ERR_VHC			   (1u<<WDG_IDX_VHC)
#define WDG_ERR_VDBUS			 (1u<<WDG_IDX_VDBUS)
#define WDG_ERR_CBUS			 (1u<<WDG_IDX_CBUS)
#define WDG_ERR_CALIB		   (1u<<WDG_IDX_CALIB)
#define WDG_ERR_ZGYRO		   (1u<<WDG_IDX_ZGYRO)
#define WDG_ERR_MOTOR1		 (1u<<WDG_IDX_MOTOR1)
#define WDG_ERR_MOTOR2		 (1u<<WDG_IDX_MOTOR2)
#define WDG_ERR_MOTOR3		 (1u<<WDG_IDX_MOTOR3)
#define WDG_ERR_MOTOR4		 (1u<<WDG_IDX_MOTOR4)
#define WDG_ERR_MOTOR5		 (1u<<WDG_IDX_MOTOR5)
#define WDG_ERR_MOTOR6		 (1u<<WDG_IDX_MOTOR6)
#define WDG_ERR_KYLIN      (1u<<WDG_IDX_KYLIN)
#define WDG_ERR_SR04F      (1u<<WDG_IDX_SR04F)
#define WDG_ERR_SR04M      (1u<<WDG_IDX_SR04M)
#define WDG_ERR_SR04L      (1u<<WDG_IDX_SR04L)
#define WDG_ERR_SR04R      (1u<<WDG_IDX_SR04R)

#define WDG_ERR_ALL ( \
		WDG_ERR_RCV | \
		WDG_ERR_TTY | \
		WDG_ERR_BTM | \
		WDG_ERR_DBI | \
		WDG_ERR_IMU | \
		WDG_ERR_VRC | \
		WDG_ERR_VHC | \
		WDG_ERR_VDBUS | \
		WDG_ERR_CBUS | \
		WDG_ERR_CALIB | \
		WDG_ERR_ZGYRO | \
		WDG_ERR_MOTOR1 | \
		WDG_ERR_MOTOR2 | \
		WDG_ERR_MOTOR3 | \
		WDG_ERR_MOTOR4 | \
		WDG_ERR_MOTOR5 | \
		WDG_ERR_MOTOR6 | \
		WDG_ERR_KYLIN | \
		WDG_ERR_SR04F | \
		WDG_ERR_SR04M | \
		WDG_ERR_SR04L | \
		WDG_ERR_SR04R \
		)

#define WDG_ERR_SIGNAL (WDG_ERR_RCV | WDG_ERR_VDBUS)
#define WDG_ERR_MOTORS (WDG_ERR_MOTOR1 | WDG_ERR_MOTOR2 | WDG_ERR_MOTOR3 | WDG_ERR_MOTOR4 | WDG_ERR_MOTOR6)

#define WDG_ERR_FATAL ( \
		WDG_ERR_RCV | \
		WDG_ERR_MOTOR1 | \
		WDG_ERR_MOTOR2 | \
		WDG_ERR_MOTOR3 | \
		WDG_ERR_MOTOR4 \
		)

#define WDG_OVERFLOW_CNT_RCV   	  100u
#define WDG_OVERFLOW_CNT_TTY  		100u
#define WDG_OVERFLOW_CNT_BTM  		100u
#define WDG_OVERFLOW_CNT_DBI  		100u
#define WDG_OVERFLOW_CNT_IMU  		100u
#define WDG_OVERFLOW_CNT_VRC  		100u
#define WDG_OVERFLOW_CNT_VHC  		100u
#define WDG_OVERFLOW_CNT_VDBUS    100u
#define WDG_OVERFLOW_CNT_CBUS  	  100u
#define WDG_OVERFLOW_CNT_CALIB  	100u
#define WDG_OVERFLOW_CNT_ZGYRO 		100u
#define WDG_OVERFLOW_CNT_MOTOR 		100u
#define WDG_OVERFLOW_CNT_KYLIN 		100u
#define WDG_OVERFLOW_CNT_SR04 		200u

#define WDG_OVERFLOW_CNT_DEFAULT \
{ \
		WDG_OVERFLOW_CNT_RCV, \
		WDG_OVERFLOW_CNT_TTY, \
		WDG_OVERFLOW_CNT_BTM, \
	  WDG_OVERFLOW_CNT_DBI, \
		WDG_OVERFLOW_CNT_IMU, \
		WDG_OVERFLOW_CNT_VRC, \
		WDG_OVERFLOW_CNT_VHC, \
		WDG_OVERFLOW_CNT_VDBUS, \
		WDG_OVERFLOW_CNT_CBUS, \
		WDG_OVERFLOW_CNT_CALIB, \
		WDG_OVERFLOW_CNT_ZGYRO, \
		WDG_OVERFLOW_CNT_MOTOR, \
		WDG_OVERFLOW_CNT_MOTOR, \
		WDG_OVERFLOW_CNT_MOTOR, \
		WDG_OVERFLOW_CNT_MOTOR, \
		WDG_OVERFLOW_CNT_MOTOR, \
		WDG_OVERFLOW_CNT_MOTOR, \
	  WDG_OVERFLOW_CNT_KYLIN, \
	  WDG_OVERFLOW_CNT_SR04, \
	  WDG_OVERFLOW_CNT_SR04, \
	  WDG_OVERFLOW_CNT_SR04, \
	  WDG_OVERFLOW_CNT_SR04, \
}

void Wdg_Init(void);
void Wdg_Proc(void);
void Wdg_Feed(uint8_t i);
void Wdg_Hang(uint8_t i);
WdgErr_t Wdg_GetErr(void);
WdgErr_t Wdg_HasErr(WdgErr_t mask);
WdgErr_t Wdg_HitErr(WdgErr_t mask);
WdgErr_t Wdg_IsOkay(void);

#ifdef __cplusplus
}
#endif

#endif

