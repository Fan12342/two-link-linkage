//
// Created by Administrator on 2026/10/23.
//

#include "TrajectoryFitter.h"
#include <cmath>

// √
void TrajectoryFitter::cal(uint32_t dt_ms)
{
    index_to_tick();
    tick_to_point(now_tick_, &now_point_);
    point_to_trajectory();
    now_index_++;
    if (now_index_ == samples_)
    {
        now_index_ = 0;
    }
}

float TrajectoryFitter::get_angle_center() const
{
    return now_trajectory_.angle_center;
}

float TrajectoryFitter::get_angle_out() const
{
    return now_trajectory_.angle_out;
}

void TrajectoryFitter::index_to_tick()
{
    // 转至 [0, 4)，便于求边
    float segment = static_cast<float>(now_index_) / static_cast<float>(samples_) * 4.0f;

    // 确定当前所在的边
    int side = static_cast<int>(segment);

    // 计算在当前边的位置，应用速度曲线
    float eased = apply_curve(segment - static_cast<float>(side), curve_type_);

    // 转换为 tick
    now_tick_ = static_cast<float>(samples_) * (static_cast<float>(side) + eased) / 4.0f;
}

void TrajectoryFitter::point_to_trajectory()
{
    constexpr float PI = 3.14159265358979323846f;

    // out 余弦值
    float cos_out = (now_point_.x * now_point_.x + now_point_.y * now_point_.y - len_center_ * len_center_ - len_out_ * len_out_)
        / (2.0f * len_center_ * len_out_);

    // 防止 arccos 越界
    if (cos_out > 1.0f) cos_out = 1.0f;
    if (cos_out < -1.0f) cos_out = -1.0f;

    float abs_rad_out = acosf(cos_out);

    // 两个方向的解
    TrajectoryData candidates[2];
    float rad_out[2] = {abs_rad_out, -abs_rad_out};

    for (int i = 0; i < 2; i++)
    {
        const float angle_center = atan2f(now_point_.y, now_point_.x)
            - atan2f(len_out_ * sinf(rad_out[i]), len_center_ + len_out_ * cosf(rad_out[i]));

        candidates[i].angle_center = remainderf(angle_center * 180.0f / PI, 360.0f);
        candidates[i].angle_out = rad_out[i] * 180.0f / PI;
    }

    // 最接近的解
    int best = 0; // 默认为第一个

    if (!is_first_)
    {
        float best_cost = 2.6e5; // 大于 (360)^2 * 2 即可

        for (int i = 0; i < 2; ++i)
        {
            const float d_center = remainderf(candidates[i].angle_center - now_trajectory_.angle_center, 360.0f);
            const float d_out = remainderf(candidates[i].angle_out - now_trajectory_.angle_out, 360.0f);

            const float cost = d_center * d_center + d_out * d_out;

            if (cost < best_cost)
            {
                best_cost = cost;
                best = i;
            }
        }
    }
    is_first_ = false;

    now_trajectory_.angle_center = (candidates[best].angle_center);
    now_trajectory_.angle_out = (candidates[best].angle_out);
}
