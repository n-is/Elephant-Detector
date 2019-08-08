/*
 * lpf.h
 * 
 * Created : 8/7/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _LPF_H_
#define _LPF_H_

#include "array.h"
#include <math.h>

template <size_t N>
void lpf(const float (&in)[N],
         float (&out)[N],
         float fc,
         uint32_t dt_millis)
{
        out[0] = in[0];
        float RC = 1.0 / (2.0*M_PI*fc);
        float dt = (float)dt_millis / 1000.0;

        float a = 1.0 / (dt + 2*RC);
        float b = 2*RC - dt;

        for (uint32_t i = 1; i < N; ++i) {
                out[i] = a * (dt * (in[i] + in[i-1]) + b * out[i-1]);
        }
}

template <size_t N>
void lpf_n(const float (&in)[N],
           float (&out)[N],
           float fc,
           uint32_t dt_millis,
           uint16_t n = 1)
{
        float mx = 1;
        float mx_inv = 1.0 / mx;
        float tmp[N];
        arrCopy(in, tmp);

        for (uint16_t i = 0; i < n; ++i) {
                mx = arrMax(tmp);
                mx_inv = 1.0 / mx;
                arrMult(tmp, mx_inv);
                lpf(tmp, out, fc, dt_millis);
                arrCopy(out, tmp);
        }

        float x = mx_inv * arrMax(in);
        arrMult(out, x);
}

template <size_t N>
void lpf(const Vec3<float> (&in)[N],
         Vec3<float> (&out)[N],
         float fc,
         uint32_t dt_millis)
{
        float in_x[N];
        float in_y[N];
        float in_z[N];
        float out_x[N];
        float out_y[N];
        float out_z[N];

        for (uint32_t i = 0; i < N; ++i) {
                in_x[i] = in[i].getX();
                in_y[i] = in[i].getY();
                in_z[i] = in[i].getZ();
        }

        lpf(in_x, out_x, fc, dt_millis);
        lpf(in_y, out_y, fc, dt_millis);
        lpf(in_z, out_z, fc, dt_millis);
        
        for (uint32_t i = 0; i < N; ++i) {
                Vec3<float> out_vec(out_x[i], out_y[i], out_z[i]);
                out[i] = out_vec;
        }
}

template <size_t N>
void lpf_n(const Vec3<float> (&in)[N],
           Vec3<float> (&out)[N],
           float fc,
           uint32_t dt_millis,
           uint16_t n = 1)
{
        float in_x[N];
        float in_y[N];
        float in_z[N];
        float out_x[N];
        float out_y[N];
        float out_z[N];

        for (uint32_t i = 0; i < N; ++i) {
                in_x[i] = in[i].getX();
                in_y[i] = in[i].getY();
                in_z[i] = in[i].getZ();
        }

        lpf_n(in_x, out_x, fc, dt_millis, n);
        lpf_n(in_y, out_y, fc, dt_millis, n);
        lpf_n(in_z, out_z, fc, dt_millis, n);

        for (uint32_t i = 0; i < N; ++i) {
                Vec3<float> out_vec(out_x[i], out_y[i], out_z[i]);
                out[i] = out_vec;
        }
}

#endif // !_LPF_H_
