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
 
#include "calib.h"

/*****************************************/
/*              Calibration              */
/*****************************************/

void Calib_GetPID(PIDCalib_t* PIDCalib, const PIDParam_t* PIDParam)
{
	PIDCalib->kp = PIDParam->kp * PID_CALIB_VALUE_SCALE;
	PIDCalib->ki = PIDParam->ki * PID_CALIB_VALUE_SCALE;
	PIDCalib->kd = PIDParam->kd * PID_CALIB_VALUE_SCALE;
	PIDCalib->Emax = PIDParam->Emax * PID_CALIB_VALUE_SCALE;
	PIDCalib->Pmax = PIDParam->Pmax * PID_CALIB_VALUE_SCALE;
	PIDCalib->Imax = PIDParam->Imax * PID_CALIB_VALUE_SCALE;
	PIDCalib->Dmax = PIDParam->Dmax * PID_CALIB_VALUE_SCALE;
	PIDCalib->Omax = PIDParam->Omax * PID_CALIB_VALUE_SCALE;
}

void Calib_SetPID(PIDParam_t* PIDParam, const PIDCalib_t* PIDCalib)
{
	PIDParam->kp = PIDCalib->kp / PID_CALIB_VALUE_SCALE;
	PIDParam->ki = PIDCalib->ki / PID_CALIB_VALUE_SCALE;
	PIDParam->kd = PIDCalib->kd / PID_CALIB_VALUE_SCALE;
	PIDParam->Emax = PIDCalib->Emax / PID_CALIB_VALUE_SCALE;
	PIDParam->Pmax = PIDCalib->Pmax / PID_CALIB_VALUE_SCALE;
	PIDParam->Imax = PIDCalib->Imax / PID_CALIB_VALUE_SCALE;
	PIDParam->Dmax = PIDCalib->Dmax / PID_CALIB_VALUE_SCALE;
	PIDParam->Omax = PIDCalib->Omax / PID_CALIB_VALUE_SCALE;
}

void Calib_GetIMU(IMUCalib_t* IMUCalib, const IMUParam_t* IMUParam)
{
	IMUCalib->ax_offset = IMUParam->ax_offset * IMU_CALIB_VALUE_SCALE;
	IMUCalib->ay_offset = IMUParam->ay_offset * IMU_CALIB_VALUE_SCALE;
	IMUCalib->az_offset = IMUParam->az_offset * IMU_CALIB_VALUE_SCALE;
	IMUCalib->gx_offset = IMUParam->gx_offset * IMU_CALIB_VALUE_SCALE;
	IMUCalib->gy_offset = IMUParam->gy_offset * IMU_CALIB_VALUE_SCALE;
	IMUCalib->gz_offset = IMUParam->gz_offset * IMU_CALIB_VALUE_SCALE;
}

void Calib_SetIMU(IMUParam_t* IMUParam, const IMUCalib_t* IMUCalib)
{
	IMUParam->ax_offset = IMUCalib->ax_offset / IMU_CALIB_VALUE_SCALE;
	IMUParam->ay_offset = IMUCalib->ay_offset / IMU_CALIB_VALUE_SCALE;
	IMUParam->az_offset = IMUCalib->az_offset / IMU_CALIB_VALUE_SCALE;
	IMUParam->gx_offset = IMUCalib->gx_offset / IMU_CALIB_VALUE_SCALE;
	IMUParam->gy_offset = IMUCalib->gy_offset / IMU_CALIB_VALUE_SCALE;
	IMUParam->gz_offset = IMUCalib->gz_offset / IMU_CALIB_VALUE_SCALE;
}

void Calib_GetMag(MagCalib_t* MagCalib, const MagParam_t* MagParam)
{
	MagCalib->mx_offset = MagParam->mx_offset * MAG_CALIB_VALUE_SCALE;
	MagCalib->my_offset = MagParam->my_offset * MAG_CALIB_VALUE_SCALE;
	MagCalib->mz_offset = MagParam->mz_offset * MAG_CALIB_VALUE_SCALE;
}

void Calib_SetMag(MagParam_t* MagParam, const MagCalib_t* MagCalib)
{
	MagParam->mx_offset = MagCalib->mx_offset / MAG_CALIB_VALUE_SCALE;
	MagParam->my_offset = MagCalib->my_offset / MAG_CALIB_VALUE_SCALE;
	MagParam->mz_offset = MagCalib->mz_offset / MAG_CALIB_VALUE_SCALE;
}

void Calib_GetVel(VelCalib_t* VelCalib, const VelParam_t* VelParam)
{
	VelCalib->x = VelParam->x * VEL_CALIB_VALUE_SCALE;
	VelCalib->y = VelParam->y * VEL_CALIB_VALUE_SCALE;
	VelCalib->z = VelParam->z * VEL_CALIB_VALUE_SCALE;
	VelCalib->e = VelParam->e * VEL_CALIB_VALUE_SCALE;
	VelCalib->c = VelParam->c * VEL_CALIB_VALUE_SCALE;
}

void Calib_SetVel(VelParam_t* VelParam, const VelCalib_t* VelCalib)
{
	VelParam->x = VelCalib->x / VEL_CALIB_VALUE_SCALE;
	VelParam->y = VelCalib->y / VEL_CALIB_VALUE_SCALE;
	VelParam->z = VelCalib->z / VEL_CALIB_VALUE_SCALE;
	VelParam->e = VelCalib->e / VEL_CALIB_VALUE_SCALE;
	VelParam->c = VelCalib->c / VEL_CALIB_VALUE_SCALE;
}

void Calib_GetMec(MecCalib_t* MecCalib, const MecParam_t* MecParam)
{
	MecCalib->lx = MecParam->lx * MEC_CALIB_VALUE_SCALE;
	MecCalib->ly = MecParam->ly * MEC_CALIB_VALUE_SCALE;
	MecCalib->r1 = MecParam->r1 * MEC_CALIB_VALUE_SCALE;
	MecCalib->r2 = MecParam->r2 * MEC_CALIB_VALUE_SCALE;
}

void Calib_SetMec(MecParam_t* MecParam, const MecCalib_t* MecCalib)
{
	MecParam->lx = MecCalib->lx / MEC_CALIB_VALUE_SCALE;
	MecParam->ly = MecCalib->ly / MEC_CALIB_VALUE_SCALE;
	MecParam->r1 = MecCalib->r1 / MEC_CALIB_VALUE_SCALE;
	MecParam->r2 = MecCalib->r2 / MEC_CALIB_VALUE_SCALE;
}

void Calib_GetPos(PosCalib_t* PosCalib, const PosParam_t* PosParam)
{
	PosCalib->ch = PosParam->ch * POS_CALIB_VALUE_SCALE;
	PosCalib->cl = PosParam->cl * POS_CALIB_VALUE_SCALE;
	PosCalib->eh = PosParam->eh * POS_CALIB_VALUE_SCALE;
	PosCalib->el = PosParam->el * POS_CALIB_VALUE_SCALE;
}

void Calib_SetPos(PosParam_t* PosParam, const PosCalib_t* PosCalib)
{
	PosParam->ch = PosCalib->ch / POS_CALIB_VALUE_SCALE;
	PosParam->cl = PosCalib->cl / POS_CALIB_VALUE_SCALE;
	PosParam->eh = PosCalib->eh / POS_CALIB_VALUE_SCALE;
	PosParam->el = PosCalib->el / POS_CALIB_VALUE_SCALE;
}



