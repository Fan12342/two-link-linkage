//
// Created by Administrator on 2026/10/24.
//

#include "two_link_linkage.h"

#include <cmath>
#include <cmath>

// 转发对应 can 数据给电机
void TwoLinkLinkage::can_callback(uint8_t* data, uint32_t stdid)
{
    if (stdid == (0x200 + motor_center_.can_id_))
        motor_center_.can_callback(data);
    else if (stdid == (0x200 + motor_center_.can_id_))
        motor_out_.can_callback(data);
}

uint8_t* TwoLinkLinkage::get_motor_data()
{
    // 将各自控制量写入 tx_data_
    motor_center_.set_tx_data(tx_data_);
    motor_center_.set_tx_data(tx_data_);

    return tx_data_;
}

void TwoLinkLinkage::update(uint32_t tick)
{
    trajectory_.cal(tick);// 计算轨迹

    // 更新角度，与电机实际角比较，选最近的角
    float angle_center = trajectory_.get_angle_center();
    float angle_out = trajectory_.get_angle_out();

    const float ref_angle_center = motor_center_.get_angle();
    const float ref_angle_out = motor_out_.get_angle();

    while (abs(angle_center - ref_angle_center) > 180.0f)
    {
        if (angle_center > ref_angle_center)
            angle_center -= 360.0f;
        else
            angle_center += 360.0f;
    }
    while (abs(angle_out - ref_angle_out) > 180.0f)
    {
        if (angle_out > ref_angle_out)
            angle_out -= 360.0f;
        else
            angle_out += 360.0f;
    }

    // 根据 PID 更新控制量
    motor_center_.update_current(angle_center);
    motor_out_.update_current(angle_out);

    // 测试用
    angle1 = angle_center;
    angle2 = angle_out;
}
