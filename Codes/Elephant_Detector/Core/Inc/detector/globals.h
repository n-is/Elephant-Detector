/*
 * globals.h
 * 
 * Created : 8/7/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "vec3.h"
#include "queue_custom.h"

#include "FreeRTOS.h"
#include "task.h"

#include "defines.h"

extern Queue<Vec3<float>, WINDOW_SIZE> gAccel_Data;
extern Queue<Vec3<float>, WINDOW_SIZE> gGyro_Data;

extern int gElephant_Detected_Count;

void DataCollection_Init();
void DataAnalysis_Init();
void Alerting_Init();

void DataCollection(uint32_t dt_millis);
void DataAnalysis(uint32_t data_sample_rate);
void Alerting();


#endif // _GLOBALS_H_
