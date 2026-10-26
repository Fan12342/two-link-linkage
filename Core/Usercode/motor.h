//
// Created by Administrator on 2026/10/24.
//

#ifndef TWO_LINK_LINKAGE_MOTOR_H
#define TWO_LINK_LINKAGE_MOTOR_H

#include "pid.h"
#include <cstdint>

class Motor
{
public:
    uint32_t can_id_;

    Motor(const uint32_t can_id, const float ratio, const uint16_t encoder_range, const PID& ppid,
          const PID& spid) : can_id_(can_id),
                                             ratio_(ratio), encoder_range_(encoder_range),
                                             half_encoder_range_(static_cast<float>(encoder_range) / 2),
                                             p_pid_(ppid), s_pid_(spid)
    {
    }

    void can_callback(uint8_t* data);
    void set_tx_data(uint8_t* tx_data);
    void update_current(float target_angle);

    float get_angle() const
    {
        return angle_degree_;
    }

private:
    float ratio_;
    uint16_t encoder_range_;
    float half_encoder_range_; // 半圈，用 float 是方便运算

    float angle_degree_ = 0.0f;
    float speed_rpm_ = 0.0f;

    uint16_t last_ecd_ = 0U;

    float target_current_ = 0.0f;

    PID p_pid_;
    PID s_pid_;
};

class Motor_3508 : public Motor
{
public:
    explicit Motor_3508(const uint32_t can_id, const PID& ppid, const PID& spid) : Motor(
        can_id, 19.2f, 8192, ppid, spid)
    {
    }
};


#endif //TWO_LINK_LINKAGE_MOTOR_H
