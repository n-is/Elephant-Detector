/*
 * queue_custom.h
 * 
 * Created : 11/16/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _QUEUE_CUSTOM_H_
#define _QUEUE_CUSTOM_H_

#include "stm32f4xx_hal.h"

template <class T, size_t q_size>
class Queue
{
public:
        Queue():head_(0), tail_(0), curr_size_(0) { }
        Queue(Queue &&) = default;
        Queue(const Queue &) = default;
        Queue &operator=(Queue &&) = default;
        Queue &operator=(const Queue &) = default;
        ~Queue() {  }

        void insert(T elem) {
                if (curr_size_ >= q_size) {
                        queue_[head_++] = elem;
                        head_ %= q_size;
                        ++tail_;
                        tail_ %= q_size;
                }
                else {
                        ++curr_size_;
                        queue_[head_++] = elem;
                        head_ %= q_size;
                }
        }

        T lookup() {
                // if( curr_size_ ) {
                --curr_size_;
                T elem = queue_[tail_++];
                tail_ %= q_size;
                return elem;
                // }
                // return 0;
        }

        uint32_t length() const { return curr_size_; }

        bool is_Empty() const { return length() == 0; }

        friend void copy_Queue(const Queue &src, Queue &dest) {
                dest.head_ = src.head_;
                dest.tail_ = src.tail_;
                dest.curr_size_ = src.curr_size_;

                uint32_t head = dest.head_;
                uint32_t tail = dest.tail_;
                uint32_t sz = dest.curr_size_;

                if (!sz) return;

                uint32_t curr_sz = 0;
                bool done = false;

                for (uint32_t i = tail; i < q_size; ++i) {
                        dest.queue_[i] = src.queue_[i];
                        if (++curr_sz >= sz) {
                                done = true;
                                break;
                        }
                }
                if (!done) {
                        for (uint32_t i = 0; i < head; ++i) {
                                dest.queue_[i] = src.queue_[i];
                                if (++curr_sz >= sz) {
                                        done = true;
                                        break;
                                }
                        }
                }
        }

        template <size_t N>
        friend uint32_t copy_QueueToArray(const Queue &src, T (&arr)[N]) {

                uint32_t head = src.head_;
                uint32_t tail = src.tail_;
                uint32_t sz = src.curr_size_;

                if (!sz) return 0;

                uint32_t curr_sz = 0;
                bool done = false;

                for (uint32_t i = tail; i < q_size; ++i) {
                        arr[curr_sz] = src.queue_[i];
                        ++curr_sz;
                        if ((curr_sz >= sz) || (curr_sz >= N)) {
                                done = true;
                                break;
                        }
                }
                if (!done) {
                        for (uint32_t i = 0; i < head; ++i) {
                                arr[curr_sz] = src.queue_[i];
                                ++curr_sz;
                                if ((curr_sz >= sz) || (curr_sz >= N)) {
                                        done = true;
                                        break;
                                }
                        }
                }

                return curr_sz;
        }

private:
        uint32_t head_, tail_, curr_size_;
        T queue_[q_size];
};

#endif // !_QUEUE_CUSTOM_H_
