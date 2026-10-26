//
// Created by Administrator on 2026/10/24.
//

#ifndef TWO_LINK_LINKAGE_PID_H
#define TWO_LINK_LINKAGE_PID_H

class PID
{
public:
    PID(float kp, float ki, float kd, float i_max, float out_max, float d_filter_k);

    void reset();
    float calc(float ref, float fdb);

private:
    float kp_, ki_, kd_;
    float i_max_, out_max_, d_filter_k_;

    float err_sum_ = 0;
    float last_err_ = 0;
    float last_d_out_ = 0;
};

#endif //TWO_LINK_LINKAGE_PID_H
