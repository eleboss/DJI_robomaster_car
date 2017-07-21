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
 
#include "dbg.h"

#if DBUG

void Dbg_Cfg(void)
{
	printf("****************** CFG ******************\n");
	printf("size of cfg: %d\n", sizeof(Cfg_t));
	printf("cfg.ver: %d\n", cfg.ver);
	printf("\tA: %u\n", (uint8_t)((cfg.ver >> 24) & 0xff));
	printf("\tB: %u\n", (uint8_t)((cfg.ver >> 16) & 0xff));
	printf("\tC: %u\n", (uint8_t)((cfg.ver >> 8) & 0xff));
	printf("\tD: %u\n", (uint8_t)(cfg.ver & 0xff));
	printf("cfg.imu: \n");
	printf("\tax_offset: %.3f\n", cfg.imu.ax_offset);
	printf("\tay_offset: %.3f\n", cfg.imu.ay_offset);
	printf("\taz_offset: %.3f\n", cfg.imu.az_offset);
	printf("\tgx_offset: %.3f\n", cfg.imu.gx_offset);
	printf("\tgy_offset: %.3f\n", cfg.imu.gy_offset);
	printf("\tgz_offset: %.3f\n", cfg.imu.gz_offset);
	printf("cfg.mag: \n");
	printf("\tmx_offset: %.3f\n", cfg.mag.mx_offset);
	printf("\tmy_offset: %.3f\n", cfg.mag.my_offset);
	printf("\tmz_offset: %.3f\n", cfg.mag.mz_offset);
	printf("cfg.rmp: \n");
	printf("\tcnt: %d\n", cfg.rmp.cnt);
	printf("cfg.vel: \n");
	printf("\tx: %.3f\n", cfg.vel.x);
	printf("\ty: %.3f\n", cfg.vel.y);
	printf("\tz: %.3f\n", cfg.vel.z);
	printf("\te: %.3f\n", cfg.vel.e);
	printf("\tc: %.3f\n", cfg.vel.c);
	printf("cfg.mec: \n");
	printf("\tlx: %.3f\n", cfg.mec.lx);
	printf("\tly: %.3f\n", cfg.mec.ly);
	printf("\tr1: %.3f\n", cfg.mec.r1);
	printf("\tr2: %.3f\n", cfg.mec.r2);
	printf("cfg.pos: \n");
	printf("\tel: %.3f\n", cfg.pos.el);
	printf("\teh: %.3f\n", cfg.pos.eh);
	printf("\tcl: %.3f\n", cfg.pos.cl);
	printf("\tch: %.3f\n", cfg.pos.ch);
	printf("cfg.cvl: \n");
	printf("\tkp: %.3f\n", cfg.cvl.kp);
	printf("\tki: %.3f\n", cfg.cvl.ki);
	printf("\tkd: %.3f\n", cfg.cvl.kd);
	printf("\tit: %.3f\n", cfg.cvl.it);
	printf("\tEmax: %.3f\n", cfg.cvl.Emax);
	printf("\tPmax: %.3f\n", cfg.cvl.Pmax);
	printf("\tImax: %.3f\n", cfg.cvl.Imax);
	printf("\tDmax: %.3f\n", cfg.cvl.Dmax);
	printf("\tOmax: %.3f\n", cfg.cvl.Omax);
	printf("cfg.gvl: \n");
	printf("\tkp: %.3f\n", cfg.gvl.kp);
	printf("\tki: %.3f\n", cfg.gvl.ki);
	printf("\tkd: %.3f\n", cfg.gvl.kd);
	printf("\tit: %.3f\n", cfg.gvl.it);
	printf("\tEmax: %.3f\n", cfg.gvl.Emax);
	printf("\tPmax: %.3f\n", cfg.gvl.Pmax);
	printf("\tImax: %.3f\n", cfg.gvl.Imax);
	printf("\tDmax: %.3f\n", cfg.gvl.Dmax);
	printf("\tOmax: %.3f\n", cfg.gvl.Omax);
	printf("cfg.gpl: \n");
	printf("\tkp: %.3f\n", cfg.gpl.kp);
	printf("\tki: %.3f\n", cfg.gpl.ki);
	printf("\tkd: %.3f\n", cfg.gpl.kd);
	printf("\tit: %.3f\n", cfg.gpl.it);
	printf("\tEmax: %.3f\n", cfg.gpl.Emax);
	printf("\tPmax: %.3f\n", cfg.gpl.Pmax);
	printf("\tImax: %.3f\n", cfg.gpl.Imax);
	printf("\tDmax: %.3f\n", cfg.gpl.Dmax);
	printf("\tOmax: %.3f\n", cfg.gpl.Omax);
	printf("\n");
}

void Dbg_Mec(void)
{
	printf("lx=%.2f,ly=%.2f,r1=%.2f,r2=%.2f\n", cfg.mec.lx, cfg.mec.ly, cfg.mec.r1, cfg.mec.r2);
}

void Dbg_Cvl(void)
{
	printf("kp=%.2f,ki=%.2f,kd=%.2f,it=%.2f\n", cfg.cvl.kp, cfg.cvl.ki, cfg.cvl.kd, cfg.cvl.it);
}

void Dbg_Gvl(void)
{
	printf("kp=%.1f,ki=%.1f,kd=%.1f,it=%.1f\n", cfg.gvl.kp, cfg.gvl.ki, cfg.gvl.kd, cfg.gvl.it);
}

void Dbg_Gpl(void)
{
	printf("kp=%.1f,ki=%.1f,kd=%.1f,it=%.1f\n", cfg.gpl.kp, cfg.gpl.ki, cfg.gpl.kd, cfg.gpl.it);
}

void Dbg_Rci(void)
{
	printf("ch0=%d,ch1=%d,ch2=%d,ch3=%d,s1=%d,s2=%d\n", 
		dbus.rcp.ch[0], dbus.rcp.ch[1], dbus.rcp.ch[2], dbus.rcp.ch[3], dbus.rcp.sw[0], dbus.rcp.sw[1]);
}

void Dbg_Hci(void)
{
	printf("k=%d,x=%d,y=%d,z=%d,l=%d,r=%d\n", 
		dbus.hcp.key.val, dbus.hcp.mouse.x, dbus.hcp.mouse.y, dbus.hcp.mouse.z,
		dbus.hcp.mouse.b[0], dbus.hcp.mouse.b[1]);
}

void Dbg_Dci(void)
{
	printf("ch0=%d,ch1=%d,ch2=%d,ch3=%d,s1=%d,s2=%d,k=%d,x=%d,y=%d,z=%d,l=%d,r=%d\n", 
		dbus.rcp.ch[0], dbus.rcp.ch[1], dbus.rcp.ch[2], dbus.rcp.ch[3], dbus.rcp.sw[0],
		dbus.rcp.sw[1], dbus.hcp.key.val, dbus.hcp.mouse.x, dbus.hcp.mouse.y, dbus.hcp.mouse.z,
		dbus.hcp.mouse.b[0], dbus.hcp.mouse.b[1]);
}

void Dbg_Cmd(void)
{
	printf("vx=%.3f,vy=%.3f,vz=%.3f,m1=%.3f,m2=%.3f,m3=%.3f,m4=%.3f\n", cmd.cv.x, cmd.cv.y, cmd.cv.z, cmd.mv.w1, cmd.mv.w2, cmd.mv.w4, cmd.mv.w4);
}

void Dbg_Odo(void)
{
	printf("px=%.3f\tpy=%.3f\tpz=%.3f\tvx=%.3f\tvy=%.3f\tvz=%.3f\n", odo.cp.x, odo.cp.y, odo.cp.z, odo.cv.x, odo.cv.y, odo.cv.z);
}

void Dbg_Wsm(void)
{
	printf("wdg=%x,ok=%d,ini=%x,ok=%d,ws=%d,lws=%d\n", Wdg_GetErr(), Wdg_IsOkay(), Ini_GetFlag(), Ini_IsDone(), Wsm_GetWs(), Wsm_GetLastWs());
}

void Dbg_Wdg(void)
{
	printf("wdg=%x,rcv=%d,fatal=%d\n", Wdg_GetErr(), Wdg_HasErr(WDG_ERR_RCV), Wdg_HasErr(WDG_ERR_FATAL));
}

void Dbg_Can(void)
{
	printf("%d\t%d\t%d\t%d\t%d\n", motor[0].id, motor[1].id, motor[2].id, motor[3].id, zgyro.id);
}

void Dbg_Ecd(void)
{
	printf("%d\t%d\t%d\t%d\n", motor[0].angle_raw, motor[1].angle_raw, motor[2].angle_raw, motor[3].angle_raw);
}

/*
void Dbg_Vrc(void)
{
	printf("ch0=%d,ch1=%d,ch2=%d,ch3=%d,s1=%d,s2=%d\n", 
		vdbus.rcp.ch[0], vdbus.rcp.ch[1], vdbus.rcp.ch[2], vdbus.rcp.ch[3], vdbus.rcp.sw[0], vdbus.rcp.sw[1]);
}

void Dbg_Vhc(void)
{
	printf("k=%d,x=%d,y=%d,z=%d,l=%d,r=%d\n", 
		vdbus.hcp.key.val, vdbus.hcp.mouse.x, vdbus.hcp.mouse.y, vdbus.hcp.mouse.z,
		vdbus.hcp.mouse.b[0], vdbus.hcp.mouse.b[1]);
}

void Dbg_Vdc(void)
{
	printf("ch0=%d,ch1=%d,ch2=%d,ch3=%d,s1=%d,s2=%d,k=%d,x=%d,y=%d,z=%d,l=%d,r=%d\n", 
		vdbus.rcp.ch[0], vdbus.rcp.ch[1], vdbus.rcp.ch[2], vdbus.rcp.ch[3], vdbus.rcp.sw[0],
		vdbus.rcp.sw[1], vdbus.hcp.key.val, vdbus.hcp.mouse.x, vdbus.hcp.mouse.y, vdbus.hcp.mouse.z,
		vdbus.hcp.mouse.b[0], vdbus.hcp.mouse.b[1]);
}
*/

void Dbg_Vcc(void)
{
	//printf("vx=%d,vy=%d,vz=%d,ve=%d,vc=%d,fs=%x\n", vcbus.vx, vcbus.vy, vcbus.vz, vcbus.pe, vcbus.pc, vcbus.fs);
}

void Dbg_Imu(void)
{
	printf("%d\t%d\n", zgyro.angle, zgyro.rate);
}

void Dbg_Ctl(void)
{
	printf("rw1=%.3f,rw2=%.3f,rw3=%.3f,rw4=%.3f,fw1=%.3f,fw2=%.3f,fw3=%.3f,fw4,c1=%.3f,c1=%.f,c2=%.f,c3=%.f,c4=%.f\n", cmd.mv.w1, cmd.mv.w2, cmd.mv.w3, cmd.mv.w4, odo.mv.w1, odo.mv.w2, odo.mv.w3, odo.mv.w4, ctl.mc.w1, ctl.mc.w2, ctl.mc.w3, ctl.mc.w4);
}

void Dbg_Srs(void)
{
	uint32_t tmp = 1 << 10;
	printf("%d, %d, %d, %d, %d, %d, %d\n", Wdg_HasErr(WDG_ERR_SR04M), srs[1].frame_cnt, srs[1].echo, srs[1].mm, srs[1].state, EXTI->RTSR & tmp, EXTI->FTSR & tmp);
}

#endif

