/*
 * energy.h
 * 
 * Created : 8/8/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _ENERGY_H_
#define _ENERGY_H_

#include "array.h"
#include <math.h>

template <size_t N>
float energy(const float (&in)[N])
{
        float tmp[N];
        arrMult(in, in, tmp);
        
        float tot_energy = arrSum(tmp);
        float inst_energy = tot_energy / (float)N;

        return inst_energy;
}

template <size_t N>
Vec3<float> energy(const Vec3<float> (&in)[N])
{
        float in_x[N];
        float in_y[N];
        float in_z[N];
        float out_x;
        float out_y;
        float out_z;

        for (uint32_t i = 0; i < N; ++i) {
                in_x[i] = in[i].getX();
                in_y[i] = in[i].getY();
                in_z[i] = in[i].getZ();
        }

        out_x = energy(in_x);
        out_y = energy(in_y);
        out_z = energy(in_z);
        
        Vec3<float> out_vec(out_x, out_y, out_z);
        return out_vec;
}

#endif // !_ENERGY_H_
