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

#include "ahrs.h"

/************************************/
/*    Attitude Heading Reference    */
/************************************/

#define PI 3.1415926f

static float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void AHRS_Config(AHRS_t* ahrs, float kp, float ki)
{
	ahrs->kp = kp;
	ahrs->ki = ki;
}

void AHRS_Update(AHRS_t* ahrs, float* buf, float halfT) {
    float norm;
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;
    float ex, ey, ez;
    float q[4];

    float q0q0 = ahrs->q[0]*ahrs->q[0];
    float q0q1 = ahrs->q[0]*ahrs->q[1];
    float q0q2 = ahrs->q[0]*ahrs->q[2];
    float q0q3 = ahrs->q[0]*ahrs->q[3];
    float q1q1 = ahrs->q[1]*ahrs->q[1];
    float q1q2 = ahrs->q[1]*ahrs->q[2];
    float q1q3 = ahrs->q[1]*ahrs->q[3];
    float q2q2 = ahrs->q[2]*ahrs->q[2];
    float q2q3 = ahrs->q[2]*ahrs->q[3];
    float q3q3 = ahrs->q[3]*ahrs->q[3];

    ax = buf[0];
    ay = buf[1];
    az = buf[2];
    gx = buf[3] * PI / 180.0f; // rad/s
    gy = buf[4] * PI / 180.0f; // rad/s
    gz = buf[5] * PI / 180.0f; // rad/s
    mx = buf[6];
    my = buf[7];
    mz = buf[8];

    norm = invSqrt(ax*ax + ay*ay + az*az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

    norm = invSqrt(mx*mx + my*my + mz*mz);
    mx = mx * norm;
    my = my * norm;
    mz = mz * norm;

    // compute reference direction of flux
    hx = 2.0f*mx*(0.5f - q2q2 - q3q3) + 2.0f*my*(q1q2 - q0q3) + 2.0f*mz*(q1q3 + q0q2);
    hy = 2.0f*mx*(q1q2 + q0q3) + 2.0f*my*(0.5f - q1q1 - q3q3) + 2.0f*mz*(q2q3 - q0q1);
    hz = 2.0f*mx*(q1q3 - q0q2) + 2.0f*my*(q2q3 + q0q1) + 2.0f*mz*(0.5f - q1q1 - q2q2);
    bx = sqrt((hx*hx) + (hy*hy));
    bz = hz;

    // estimated direction of gravity and flux (v and w)
    vx = 2.0f*(q1q3 - q0q2);
    vy = 2.0f*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    wx = 2.0f*bx*(0.5f - q2q2 - q3q3) + 2.0f*bz*(q1q3 - q0q2);
    wy = 2.0f*bx*(q1q2 - q0q3) + 2.0f*bz*(q0q1 + q2q3);
    wz = 2.0f*bx*(q0q2 + q1q3) + 2.0f*bz*(0.5f - q1q1 - q2q2);

    // error is sum of cross product between reference direction of fields and direction measured by sensors
    ex = (ay*vz - az*vy) + (my*wz - mz*wy);
    ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
    ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

    if(ex != 0.0f && ey != 0.0f && ez != 0.0f)
    {
    	ahrs->exInt = ahrs->exInt + ex * ahrs->ki * halfT;
    	ahrs->eyInt = ahrs->eyInt + ey * ahrs->ki * halfT;
    	ahrs->ezInt = ahrs->ezInt + ez * ahrs->ki * halfT;
        gx = gx + ahrs->kp*ex + ahrs->exInt;
        gy = gy + ahrs->kp*ey + ahrs->eyInt;
        gz = gz + ahrs->kp*ez + ahrs->ezInt;
    }

    q[0] = ahrs->q[0] + (-ahrs->q[1]*gx - ahrs->q[2]*gy - ahrs->q[3]*gz)*halfT;
    q[1] = ahrs->q[1] + ( ahrs->q[0]*gx + ahrs->q[2]*gz - ahrs->q[3]*gy)*halfT;
    q[2] = ahrs->q[2] + ( ahrs->q[0]*gy - ahrs->q[1]*gz + ahrs->q[3]*gx)*halfT;
    q[3] = ahrs->q[3] + ( ahrs->q[0]*gz + ahrs->q[1]*gy - ahrs->q[2]*gx)*halfT;

    norm = invSqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    ahrs->q[0] = q[0] * norm;
    ahrs->q[1] = q[1] * norm;
    ahrs->q[2] = q[2] * norm;
    ahrs->q[3] = q[3] * norm;
}

void AHRS_Q2Euler(float* q, Euler_t* euler)
{
	euler->yaw = -atan2(2*q[1]*q[2] + 2*q[0]*q[3], -2*q[2]*q[2] - 2*q[3]*q[3] + 1)*180/PI; // yaw    -pi----pi
	euler->pitch = -asin(-2*q[1]*q[3] + 2*q[0]*q[2])*180/PI; // pitch    -pi/2    --- pi/2
	euler->roll = atan2(2*q[2]*q[3] + 2*q[0]*q[1], -2*q[1]*q[1] - 2*q[2]*q[2] + 1)*180/PI; // roll  -pi-----pi
}
