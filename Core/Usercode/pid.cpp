//
// Created by Administrator on 2026/10/24.
//

#include "pid.h"

PID::PID(float kp, float ki, float kd, float i_max, float out_max, float d_filter_k):
    kp_(kp), ki_(ki), kd_(kd), i_max_(i_max), out_max_(out_max), d_filter_k_(d_filter_k) {}

void PID::reset()
{
    err_sum_ = 0;
    last_err_ = 0;
}

float PID::calc(float ref, float fdb)
{
    float error = ref - fdb;

    float p_out = kp_ * error;

    float i_out = 0;
    if (error < i_max_ && error > -i_max_)
    {
        err_sum_ += error;
        i_out = ki_ * err_sum_;
    }
    else
    {
        err_sum_ = 0;
    }

    last_d_out_ = (1 - d_filter_k_) * last_d_out_ + d_filter_k_ * kd_ * (error - last_err_);

    last_err_ = error;

    float out = p_out + i_out + last_d_out_;
    out = (out < out_max_) ? out : out_max_;
    out = (out > -out_max_) ? out : -out_max_;

    return out;
}