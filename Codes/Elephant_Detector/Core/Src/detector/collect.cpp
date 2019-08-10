/*
 * collect.cpp
 * 
 * Created : 8/7/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "globals.h"
#include "devs_config.h"
#include "cmsis_os.h"

static Vec3<float> gAccel_Bias;
static Vec3<float> gGyro_Bias;

void DataCollection_Init()
{
        // Switch on the MPU
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
        // Wait for the IMU to switch on properly
        osDelay(500);
        IMU_Init();
        osDelay(500);

        gAccel_Bias = MPU6050_Calc_AccelBias(&Body_IMU, 500);
        gGyro_Bias = MPU6050_Calc_GyroBias(&Body_IMU, 500);
}

void print_DataQueue(Queue<Vec3<float>, WINDOW_SIZE> data_queue)
{
        
        Vec3<float> data[WINDOW_SIZE];
        copy_QueueToArray(data_queue, data);

        for (uint8_t j = 0; j < WINDOW_SIZE; ++j) {
                data[j].print();
                printf("    ");
        }
        printf("\n");
}

void DataCollection(uint32_t dt_millis)
{
        Vec3<float> accel, gyro;
        
        MPU6050_Read_NormAxes(&Body_IMU);
        accel = Body_IMU.norm_a_axis - gAccel_Bias;
        gyro = Body_IMU.norm_g_axis - gGyro_Bias;

        // accel.print();
        // printf(", ");
        // gyro.print();
        // printf("\n");

        taskENTER_CRITICAL();
        gAccel_Data.insert(accel);
        gGyro_Data.insert(gyro);
        taskEXIT_CRITICAL();
}
