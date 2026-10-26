//
// Created by Administrator on 2026/10/24.
//

#include "motor.h"

void Motor::can_callback(uint8_t* data)
{
    uint16_t now_ecd = data[0] << 8 | data[1];

    int16_t speed = static_cast<int16_t>(data[2] << 8 | data[3]);
    speed_rpm_ = static_cast<float>(speed) / ratio_;

    float delta_angle = static_cast<float>(now_ecd) - static_cast<float>(last_ecd_);
    if (delta_angle <= -half_encoder_range_)
        delta_angle += half_encoder_range_;
    else if (delta_angle >= half_encoder_range_)
        delta_angle -= half_encoder_range_;
    angle_degree_ += delta_angle * 360 / encoder_range_ / ratio_;
    last_ecd_ = now_ecd;
}

void Motor::set_tx_data(uint8_t* tx_data)
{
    int16_t data;
    if (target_current_ > 20)
        data = 16384;
    else if (target_current_ < -20)
        data = -16384;
    else
        data = static_cast<int16_t>(target_current_ * 16384 / 20);

    tx_data[can_id_ * 2 - 2] = data >> 8;
    tx_data[can_id_ * 2 - 1] = data & 0xff;
}

void Motor::update_current(float target_angle)
{
    float current = 0.0;
    float s_ref = p_pid_.calc(target_angle, angle_degree_);
    current = s_pid_.calc(s_ref, speed_rpm_);

    target_current_ = current;

    // 测试用
    // angle_degree_ = target_angle;
}
