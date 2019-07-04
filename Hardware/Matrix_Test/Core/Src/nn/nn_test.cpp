/*
 * nn_test.cpp
 * 
 * Created : 6/4/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "matrix.h"

extern float32_t Theta1_Arr[25*401];
extern float32_t Theta2_Arr[10*26];
extern float32_t X1_Arr[1*401];

float32_t Theta1_trans_Arr[401*25];
float32_t Theta2_trans_Arr[26*10];

float32_t H1_Arr[1*25];
float32_t H2_Arr[1*10];

float32_t H1_Bias_Arr[1*26];

void nn_test()
{
        uint32_t start_time = HAL_GetTick();
        Matrix Theta1(25,401, Theta1_Arr);
        Matrix Theta2(10,26, Theta2_Arr);

        Matrix Theta1_trans(401, 25, Theta1_trans_Arr);
        Matrix Theta2_trans( 26, 10, Theta2_trans_Arr);

        Matrix H1(1, 25, H1_Arr);
        Matrix H2(1, 10, H2_Arr);

        Matrix X1(1, 401, X1_Arr);

        trans_Matrix(Theta1, Theta1_trans);
        trans_Matrix(Theta2, Theta2_trans);

        mult_Matrix(X1, Theta1_trans, H1);
        sigmoid_EW(H1);

        Matrix H1_Bias(1, 26, H1_Bias_Arr);
        H1_Bias.at(0,0) = 1;
        H1_Bias.fill(0, 1, H1);

        mult_Matrix(H1_Bias, Theta2_trans, H2);
        sigmoid_EW(H2);

        H2.print();
        
        uint32_t end_time = HAL_GetTick();

        printf("\nTotal Time Taken : %ld\n", (int32_t)(end_time - start_time));

}
