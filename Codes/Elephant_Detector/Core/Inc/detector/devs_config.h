/*
 * devs_config.h
 * 
 * Created : 8/7/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _DEVS_CONFIG_H_
#define _DEVS_CONFIG_H_

#include "mpu6050.h"

// These are the main IMU of the System
extern struct MPU6050 Body_IMU;


void IMU_Init();

#endif // !_DEVS_CONFIG_H_
