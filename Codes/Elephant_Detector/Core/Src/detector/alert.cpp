/*
 * alert.cpp
 * 
 * Created : 8/8/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "globals.h"
#include "lpf.h"
#include "energy.h"
#include "string.h"

#include "usart.h"
#include "cmsis_os.h"

void Alerting_Init()
{
        // Switch on the GSM Module
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
        // Wait for the GSM module to be ready
        // osDelay(15000);
}

const char * gSMS_Start_Command[2] = {  "AT+CMGF=1\r\n",
                                        "AT+CMGS=\"+9779867375476\"\r\r\n" };

const char * gElephant_String = "Elephant Detected!! elephant detected!! Elephant/elephant detected!!\r\n";

static uint8_t gSMS_End_Command[3] = {26, '\r', '\n'};

static uint32_t gAlerted_Time = 0;
void Alerting()
{
        uint32_t alert_duration = 0;
        uint32_t curr_tick = HAL_GetTick();
        if (gAlerted_Time > curr_tick) {
                alert_duration = 4294967295 - gAlerted_Time + curr_tick;
        }
        else {
                alert_duration = curr_tick - gAlerted_Time;
        }
        // printf("Alert Duration : %ld\n", alert_duration);

        if (alert_duration >= 1000*60*1) {       // 1 minute alert duration

                // printf("Alert Duration\n");
                HAL_GPIO_WritePin(BLED_3_GPIO_Port, BLED_3_Pin, GPIO_PIN_SET);

                if (gElephant_Detected_Count > 2) {

                        printf("gElephant Detect\n");

                        taskENTER_CRITICAL();
                        gElephant_Detected_Count = 0;
                        taskEXIT_CRITICAL();

                        gAlerted_Time = HAL_GetTick();

                        HAL_GPIO_WritePin(BLED_1_GPIO_Port, BLED_1_Pin, GPIO_PIN_SET);

                        for (uint8_t i = 0; i < 2; ++i) {
                                HAL_UART_Transmit(&huart2,
                                                  (uint8_t *)gSMS_Start_Command[i],
                                                  strlen(gSMS_Start_Command[i]),
                                                  1000);
                                osDelay(1000);
                        }
                        HAL_UART_Transmit(&huart2, (uint8_t *)gElephant_String, strlen(gElephant_String), 1000);
                        osDelay(1000);
                        HAL_UART_Transmit(&huart2, gSMS_End_Command, 3, 1000);
                        osDelay(1000);

                        HAL_GPIO_WritePin(BLED_1_GPIO_Port, BLED_1_Pin, GPIO_PIN_RESET);
                }
        }
        else {
                HAL_GPIO_WritePin(BLED_3_GPIO_Port, BLED_3_Pin, GPIO_PIN_RESET);
        }
}
