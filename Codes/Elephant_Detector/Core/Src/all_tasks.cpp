/*
 * all_tasks.cpp
 * 
 * Created : 8/7/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "globals.h"

/* Export Functions Used in C */
extern "C" void StartDefaultTask(void const *argument);
extern "C" void DataCollection_Thread(void const *argument);
extern "C" void DataAnalysis_Thread(void const *argument);
extern "C" void Alerting_Thread(void const *argument);

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument)
{

        /* USER CODE BEGIN StartDefaultTask */
        /* Infinite loop */
        for (;;)
        {
                osDelay(500);
        }
        /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_DataCollection_Thread */
/**
* @brief Function implementing the DataCollection thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DataCollection_Thread */
void DataCollection_Thread(void const *argument)
{
        /* USER CODE BEGIN DataCollection_Thread */
        uint32_t sample_period = DATA_SAMPLE_PERIOD_MILLIS;

        uint32_t dt = HAL_GetTick();
        uint32_t dt_tmp = HAL_GetTick();
        uint32_t last_run_time = 0;

        DataCollection_Init();
        HAL_GPIO_WritePin(BLED_2_GPIO_Port, BLED_2_Pin, GPIO_PIN_SET);

        osDelay(sample_period);

        /* Infinite loop */
        for (;;)
        {
                // Since this is the highest priority task, we can be sure that
                // another task won't start when this task is running
                dt_tmp = HAL_GetTick();
                dt = dt_tmp - dt;

                // Collect Data Here
                DataCollection(sample_period);

                // for (uint32_t i = 0; i < 100; ++i) {
                //         printf("%ld, %ld\n", dt + last_run_time, i);
                // }
  
                dt = HAL_GetTick();
                dt_tmp = dt - dt_tmp;
                last_run_time = dt_tmp;

                // Check for timing Issues
                if (last_run_time > sample_period / 2) {
                        // Timing Issue Occured since run time is more than half
                        // of sample time
                }

                // Sleep for remaining time of the sampling period if there is
                // time left
                if (dt_tmp < sample_period) {
                        osDelay(sample_period - dt_tmp);
                }
        }
        /* USER CODE END DataCollection_Thread */
}

/* USER CODE BEGIN Header_DataAnalysis_Thread */
/**
* @brief Function implementing the DataAnalysis thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DataAnalysis_Thread */
void DataAnalysis_Thread(void const *argument)
{
        /* USER CODE BEGIN DataAnalysis_Thread */
        uint32_t sample_period = 100;

        uint32_t dt = HAL_GetTick();
        uint32_t dt_tmp = HAL_GetTick();
        uint32_t last_run_time = 0;

        osDelay(sample_period);

        /* Infinite loop */
        for (;;)
        {
                // Start Analysis only if the first buffer has been filled
                if (gAccel_Data.length() >= WINDOW_SIZE && gGyro_Data.length() >= WINDOW_SIZE) {
                        // Since this is the highest priority task, we can be sure that
                        // another task won't start when this task is running
                        dt_tmp = HAL_GetTick();
                        dt = dt_tmp - dt;

                        // Analyse Data Here
                        DataAnalysis(DATA_SAMPLE_PERIOD_MILLIS);

                        // for (uint32_t i = 0; i < 100; ++i) {
                        //         printf("%ld, %ld\n", dt + last_run_time, i);
                        // }
        
                        dt = HAL_GetTick();
                        dt_tmp = dt - dt_tmp;
                        last_run_time = dt_tmp;

                        // Check for timing Issues
                        if (last_run_time > sample_period / 2) {
                                // Timing Issue Occured since run time is more than half
                                // of sample time
                        }

                        // Sleep for remaining time of the sampling period if there is
                        // time left
                        if (dt_tmp < sample_period) {
                                osDelay(sample_period - dt_tmp);
                        }
                }
        }
        /* USER CODE END DataAnalysis_Thread */
}

/* USER CODE BEGIN Header_Alerting_Thread */
/**
* @brief Function implementing the Alerting thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Alerting_Thread */
void Alerting_Thread(void const *argument)
{
        /* USER CODE BEGIN Alerting_Thread */
        uint32_t loop_period = 500;

        uint32_t dt = HAL_GetTick();
        uint32_t dt_tmp = HAL_GetTick();
        uint32_t last_run_time = 0;

        Alerting_Init();

        osDelay(loop_period);

        /* Infinite loop */
        for (;;)
        {
                // Since this is the highest priority task, we can be sure that
                // another task won't start when this task is running
                dt_tmp = HAL_GetTick();
                dt = dt_tmp - dt;

                // Alert User Here
                Alerting();

                // for (uint32_t i = 0; i < 100; ++i) {
                //         printf("%ld, %ld\n", dt + last_run_time, i);
                // }
  
                dt = HAL_GetTick();
                dt_tmp = dt - dt_tmp;
                last_run_time = dt_tmp;

                // Check for timing Issues
                if (last_run_time > loop_period / 2) {
                        // Timing Issue Occured since run time is more than half
                        // of sample time
                }

                // Sleep for remaining time of the loop period if there is
                // time left
                if (dt_tmp < loop_period) {
                        osDelay(loop_period - dt_tmp);
                }
        }
        /* USER CODE END Alerting_Thread */
}
