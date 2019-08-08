/*
 * globals.cpp
 * 
 * Created : 8/7/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "globals.h"

Queue<Vec3<float>, WINDOW_SIZE> gAccel_Data;
Queue<Vec3<float>, WINDOW_SIZE> gGyro_Data;

int gElephant_Detected_Count = 0;
