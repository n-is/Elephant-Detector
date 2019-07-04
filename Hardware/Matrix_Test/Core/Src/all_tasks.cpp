/*
 * all_tasks.cpp
 * 
 * Created : 6/17/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "matrix.h"


extern "C" void StartDefaultTask(void const *argument);
extern "C" void NN_Thread(void const *argument);

void nn_test();

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
                osDelay(1);
        }
        /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_NN_Thread */
/**
* @brief Function implementing the NN_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_NN_Thread */
void NN_Thread(void const *argument)
{
        /* USER CODE BEGIN NN_Thread */

        nn_test();

        /* Infinite loop */
        for (;;)
        {
                osDelay(1);
        }
        /* USER CODE END NN_Thread */
}
