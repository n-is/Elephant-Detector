/*
 * devs_config.cpp
 * 
 * Created : 11/9/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

/**
 * @file  : devs_config.cpp
 * @brief : All the hardware specific configurations of all devices are done in
 *          this file.
 */

#include "devs_config.h"

struct MPU6050 Body_IMU;


void IMU_Init()
{
        Body_IMU.hi2c = &hi2c1;
        Body_IMU.address = 0xD0;
        Body_IMU.a_scale = Accel_Scale::SCALE_2G;
        Body_IMU.g_scale = Gyro_Scale::SCALE_250;

        MPU6050_Init(&Body_IMU);
}
