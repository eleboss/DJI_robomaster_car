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

#include "cfg.h"

/*************************************/
/*           Configuration           */
/*************************************/

uint8_t cfg_sync_flag = 0;

Cfg_t cfg = CFG_DEF;

void Cfg_Load(Cfg_t* cfg)
{
	Fos_Read((uint8_t*)cfg, sizeof(Cfg_t));
}

uint8_t Cfg_Save(Cfg_t* cfg)
{
	return Fos_Write((uint8_t*)cfg, sizeof(Cfg_t));
}

CfgVer_t Cfg_GetVer(void)
{
	return cfg.ver;
}

void Cfg_SetVer(CfgVer_t ver)
{
	cfg.ver = ver;
}

CfgFlg_t Cfg_GetFlag(CfgFlg_t flag)
{
	return Flag_Get(&cfg.flg, flag);
}

void Cfg_SetFlag(CfgFlg_t flag)
{
	Flag_Set(&cfg.flg, flag);
}

void Cfg_ClrFlag(CfgFlg_t flag)
{
	Flag_Clr(&cfg.flg, flag);
}

uint8_t Cfg_IsSynced(void)
{
	return cfg_sync_flag == 0;
}

void Cfg_SetSyncFlag(uint8_t flag)
{
	cfg_sync_flag = flag;
}

void Cfg_Init(void)
{
	Cfg_t tmp = CFG_DEF;
	Cfg_Load(&cfg);
	if (!Cfg_GetFlag(CFG_FLAG_IMU)) {
		memcpy(&cfg.imu, &tmp.imu, sizeof(IMUCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_MAG)) {
		memcpy(&cfg.mag, &tmp.mag, sizeof(MagCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_RMP)) {
		memcpy(&cfg.rmp, &tmp.rmp, sizeof(RmpCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_VEL)) {
		memcpy(&cfg.vel, &tmp.vel, sizeof(VelCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_MEC)) {
		memcpy(&cfg.mec, &tmp.mec, sizeof(MecCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_POS)) {
		memcpy(&cfg.pos, &tmp.pos, sizeof(PosCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_CVL)) {
		memcpy(&cfg.cvl, &tmp.cvl, sizeof(PIDCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_CPL)) {
		memcpy(&cfg.cpl, &tmp.cpl, sizeof(PIDCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_GVL)) {
		memcpy(&cfg.gvl, &tmp.gvl, sizeof(PIDCfg_t));
	}
	if (!Cfg_GetFlag(CFG_FLAG_GPL)) {
		memcpy(&cfg.gpl, &tmp.gpl, sizeof(PIDCfg_t));
	}
	cfg_sync_flag = 0;
}

void Cfg_Proc(void)
{
	if (cfg_sync_flag == 1) {
		Cfg_Save(&cfg);
		cfg_sync_flag = 0;
	}
}

void Cfg_Reset(void)
{
	Cfg_t tmp = CFG_DEF;
	Cfg_Save(&tmp);
	Cfg_Init();
}



