/*
 * analyze.cpp
 * 
 * Created : 8/7/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "globals.h"
#include "lpf.h"
#include "energy.h"
#include "string.h"

#include "usart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

void DataAnalysis_Init()
{

}

void print_VectorArray(Vec3<float> vec[WINDOW_SIZE])
{
        printf("[\n");
        for (uint32_t i = 0; i < WINDOW_SIZE; ++i) {
                printf("[");
                (vec[i].mult_EW(1000.0)).print();
                printf("]");
                if (i != WINDOW_SIZE - 1) {
                        printf(";");
                }
                printf("\n");
        }
        printf("]\n");
}

void DataAnalysis(uint32_t data_sample_rate)
{
        Vec3<float> curr_accel[WINDOW_SIZE], curr_gyro[WINDOW_SIZE];

        taskENTER_CRITICAL();
        copy_QueueToArray(gAccel_Data, curr_accel);
        copy_QueueToArray(gGyro_Data, curr_gyro);
        taskEXIT_CRITICAL();

        Vec3<float> f_ca[WINDOW_SIZE];
        Vec3<float> f_ga[WINDOW_SIZE];

        lpf_n(curr_accel, f_ca, 100, data_sample_rate, 20);
        lpf_n(curr_gyro, f_ga, 100, data_sample_rate, 20);

        Vec3<float> accel_energy = energy(f_ca);
        Vec3<float> gyro_energy = energy(f_ga);

        float tot_accel_energy = accel_energy.sum();
        float tot_gyro_energy = gyro_energy.sum();

        if (tot_gyro_energy > 10 && tot_accel_energy > 0) {
                // Elephant Detected
                HAL_GPIO_WritePin(BLED_4_GPIO_Port, BLED_4_Pin, GPIO_PIN_SET);

                taskENTER_CRITICAL();
                ++gElephant_Detected_Count;
                taskEXIT_CRITICAL();
        }
}
