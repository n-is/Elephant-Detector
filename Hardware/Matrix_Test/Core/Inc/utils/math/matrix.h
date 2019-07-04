/*
 * matrix.h
 * 
 * Created : 6/17/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "stm32f407xx.h"
#include "arm_math.h"
#include "stm32f4xx_hal.h"

class Matrix
{
public:
        Matrix(uint16_t row, uint16_t col, float32_t *data) {

                rows_ = row;
                cols_ = col;
                data_ = data;
                arm_mat_init_f32(&S_, rows_, cols_, data_);
        }

        template <size_t M, size_t N>
        Matrix(float (&mat)[M][N]) : Matrix(M, N, (float32_t *)mat) { }

        Matrix(Matrix &&) = default;
        Matrix(const Matrix &m) = delete;
        Matrix &operator=(Matrix &&) = default;
        Matrix &operator=(const Matrix &m) = delete;
        ~Matrix() { }
        
        inline float &at(uint16_t i, uint16_t j) {
                return data_[i*cols_ + j];
        }        

        template <size_t M, size_t N>
        void fill(const float (&mat)[M][N]) {
                for (uint8_t i = 0; i < M; ++i) {
                        for (uint8_t j = 0; j < N; ++j) {
                                data_[i*cols_ + j] = mat[i][j];
                        }
                }
        }

        void fill(const float val) {
                for (uint8_t i = 0; i < rows_; ++i) {
                        for (uint8_t j = 0; j < cols_; ++j) {
                                data_[i*cols_ + j] = val;
                        }
                }
        }

        void fill(uint16_t si, uint16_t sj, Matrix &m) {

                uint16_t start = si*cols_ + sj;
                uint16_t blk_sz = m.rows_ * m.cols_;
                arm_copy_f32(m.data_, &data_[start], blk_sz);

        }

        friend arm_status add_Matrix(const Matrix &src1, const Matrix &src2, Matrix &dest) {
                return arm_mat_add_f32(&src1.S_, &src2.S_, &dest.S_);
        }

        friend arm_status sub_Matrix(const Matrix &src1, const Matrix &src2, Matrix &dest) {
                return arm_mat_sub_f32(&src1.S_, &src2.S_, &dest.S_);
        }

        friend arm_status mult_Matrix(const Matrix &src1, const Matrix &src2, Matrix &dest) {
                return arm_mat_mult_f32(&src1.S_, &src2.S_, &dest.S_);
        }

        friend arm_status scale_Matrix(const Matrix &src, float k, Matrix &dest) {
                return arm_mat_scale_f32(&src.S_, k, &dest.S_);
        }

        friend arm_status trans_Matrix(const Matrix &src, Matrix &dest) {
                return arm_mat_trans_f32(&src.S_, &dest.S_);
        }

        friend arm_status inverse_Matrix(const Matrix &src, Matrix &dest) {
                return arm_mat_inverse_f32(&src.S_, &dest.S_);
        }

        friend void sigmoid_EW(Matrix &m) {
                for (uint8_t i = 0; i < m.rows_; ++i) {
                        for (uint8_t j = 0; j < m.cols_; ++j) {
                                float z = m.at(i,j);
                                m.at(i,j) = 1.0 / (1.0 + exp(z));
                        }
                }
        }
        
        void print() const {
                for (uint8_t i = 0; i < rows_; ++i) {
                        for (uint8_t j = 0; j < cols_; ++j) {
                                printf("%ld\t", (int32_t)data_[i*cols_ + j]);
                        }
                        printf("\n");
                }
        }

private:
        arm_matrix_instance_f32 S_;
        uint16_t rows_;
        uint16_t cols_;
        float32_t *data_;
};

#endif // !_MATRIX_H_
