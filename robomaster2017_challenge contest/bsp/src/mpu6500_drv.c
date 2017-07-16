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

#include "mpu6500_drv.h"

uint8_t MPU6500_CheckDevice(void)
{
	uint8_t data = 0;
	uint8_t flag = MPU6500_SPI_Read_Reg(MPU6500_WHO_AM_I, &data);
	flag &= (data == MPU6500_ID);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);
	return 1;
}

uint8_t MPU6500_Init(void)
{
	#define MPU6500_INIT_DATA_CNT 10
  uint8_t MPU6500_Init_Data[MPU6500_INIT_DATA_CNT][2] = 
  {
    {MPU6500_PWR_MGMT_1,     0x80},      // Reset Device
    {MPU6500_PWR_MGMT_1,     0x03},      // Clock Source - Gyro-Z
    {MPU6500_PWR_MGMT_2,     0x00},      // Enable Acc & Gyro
    {MPU6500_CONFIG,         0x02},      // LPF 98Hz
    {MPU6500_GYRO_CONFIG,    0x18},      // +-2000dps
    {MPU6500_ACCEL_CONFIG,   0x10},      // +-8G
    {MPU6500_ACCEL_CONFIG_2, 0x02},      // enable LowPassFilter  Set Acc LPF
    {MPU6500_USER_CTRL,      0x20},      // Enable AUX
  };
	
	uint8_t flag = 0;
	uint8_t i = 0;
	
	flag = MPU6500_CheckDevice();
	RETURN_ZERO_IF_ASSERT_FAILED(flag);
	
	for(i = 0; i < MPU6500_INIT_DATA_CNT; i++)
  {
    flag = MPU6500_SPI_Write_Reg(MPU6500_Init_Data[i][0], MPU6500_Init_Data[i][1]);
		RETURN_ZERO_IF_ASSERT_FAILED(flag);
  }

	return 1;
}

uint8_t MPU6500_INT_Enable(void)
{
	uint8_t flag = 0;

	flag = MPU6500_SPI_Write_Reg(MPU6500_SMPLRT_DIV, 0x01);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	flag = MPU6500_SPI_Write_Reg(MPU6500_INT_ENABLE, 0x01);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	return 1;
}

uint8_t MPU6500_Read(int16_t* data)
{
	uint8_t buf[MPU6500_DATA_SIZE];
	uint8_t flag = 0;
	uint8_t i = 0;
	for (i = 0; i < MPU6500_DATA_SIZE; i++) {
		flag = MPU6500_SPI_Read_Reg(MPU6500_ACCEL_XOUT_H, &buf[i]);
		RETURN_ZERO_IF_ASSERT_FAILED(flag);
	}
	
	data[0] = (((int16_t)buf[0]) << 8) | buf[1];
	data[1] = (((int16_t)buf[2]) << 8) | buf[3];
	data[2] = (((int16_t)buf[4]) << 8) | buf[5];
	
	data[3] = (((int16_t)buf[6]) << 8) | buf[7];
	
	data[4] = (((int16_t)buf[8]) << 8) | buf[9];
	data[5] = (((int16_t)buf[10]) << 8) | buf[11];
	data[6] = (((int16_t)buf[12]) << 8) | buf[13];

	return 1;
}


