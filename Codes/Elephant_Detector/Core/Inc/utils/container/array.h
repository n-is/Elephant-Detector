/*
 * array.h
 *
 * Created : 23/2/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _ARRAY_CONTAINER_H_
#define _ARRAY_CONTAINER_H_

#include "stm32f4xx.h"

template <typename T, size_t N>
size_t arrSize(const T (&arr)[N])
{
        return N;
}

template <size_t N>
void arrPrint(const float (&arr)[N])
{
        printf("[ ");
        for (size_t i = 0; i < N; ++i) {
                printf("%ld ", (int32_t)(arr[i]*1000.0));
        }
        printf("]");
}

template <size_t N>
void arrPrint(const uint8_t (&arr)[N])
{
        printf("[ ");
        for (size_t i = 0; i < N; ++i) {
                printf("%d ", (uint8_t)(arr[i]));
        }
        printf("]");
}

template <size_t N>
void arrMult(float (&arr)[N], float num)
{
        for (size_t i = 0; i < N; ++i) {
                arr[i] *= num;
        }
}

template <size_t N>
float arrSum(float (&arr)[N])
{
        float sum = 0;
        for (size_t i = 0; i < N; ++i) {
                sum += arr[i];
        }
        return sum;
}

template <size_t N>
void arrMult(const float (&arr1)[N], const float (&arr2)[N], float (&dst)[N])
{
        for (size_t i = 0; i < N; ++i) {
                dst[i] = arr1[i]*arr2[i];
        }
}

template<typename T, size_t N>
void arrFill(T (&arr)[N], T num)
{
        for (size_t i = 0; i < N; ++i) {
                arr[i] = num;
        }
}

// Only works with datatypes with defined == operator. Doesn't with float/double.
// Returns the first index of the element
template <typename T, size_t N>
int arrIndex(T (&arr)[N], T elem)
{
        for (size_t i = 0; i < N; ++i) {
                if (arr[i] == elem) {
                        return (int)i;
                }
        }
        return -1;
}

template <typename T, size_t N>
void arrCopy(const T (&src)[N], T (&dest)[N])
{
        for (size_t i = 0; i < N; ++i) {
                dest[i] = src[i];
        }
}

template <typename T, size_t N, size_t M>
void arrCopy(const T (&src)[N][M], T (&dest)[N][M])
{
        for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < M; ++j) {
                        dest[i][j] = src[i][j];
                }
        }
}

template <typename T>
T max(T x, T y)
{
        return (x > y)? x:y;
}

template <typename T, size_t N>
T arrMax(const T (&src)[N])
{
        T mx = src[0];
        for (size_t i = 1; i < N; ++i) {
                mx = max(mx, src[i]);
        }
        return mx;
}

template <typename T, size_t N>
T arrMin(const T (&src)[N])
{
        T mn = src[0];
        for (size_t i = 1; i < N; ++i) {
                mn = min(mn, src[i]);
        }
        return mn;
}

// void copy_Buffer(const float *src, float *dst, uint32_t len)
// {
//         for (uint32_t i = 0; i < len; ++i) {
//                 dst[i] = src[i];
//         }
// }

// float max_Buffer(const float *src, uint16_t len)
// {
//         float mx = src[0];
//         for (size_t i = 1; i < len; ++i) {
//                 mx = max(mx, src[i]);
//         }
//         return mx;
// }

// void div_Buffer(const float *src, float *dst, float num, uint16_t len)
// {
//         for (uint32_t i = 0; i < len; ++i) {
//                 dst[i] = src[i] / num;
//         }
// }

#endif // !_ARRAY_CONTAINER_H_
