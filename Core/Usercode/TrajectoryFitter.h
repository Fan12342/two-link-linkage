//
// Created by Administrator on 2026/10/23.
//

#ifndef IMA_TRAJECTORY_H
#define IMA_TRAJECTORY_H

#include "curve.h"
#include <cstdint>

class TrajectoryFitter
{
    public:
    virtual ~TrajectoryFitter() = default;

    // 轨迹状态
    struct TrajectoryData
    {
        float angle_center;
        float angle_out;
    };

    // 点
    struct PointData
    {
        float x, y;
    };

    TrajectoryFitter(const uint32_t samples, const float len_center, const float len_out) : samples_(samples),
        len_center_(len_center), len_out_(len_out)
    {
    };
    void cal(uint32_t dt_ms); // 目前没有用 dt_ms 插值
    float get_angle_center() const;
    float get_angle_out() const;

private:
    // 缓动曲线
    CurveType curve_type_ = CurveType::SmoothStep;

    // 已知数据保存
    uint32_t samples_; // 拟合点数
    float len_center_;
    float len_out_;

    bool is_first_ = true;

    // 记录当前状态
    uint32_t now_index_ = 0;
    float now_tick_ = 0.0f;
    PointData now_point_ = PointData();
    TrajectoryData now_trajectory_ = TrajectoryData();

    void index_to_tick();
    // void tick_to_point(); // 在下面，纯虚函数
    void point_to_trajectory();

protected:
    virtual void tick_to_point(float tick, PointData* point) = 0;
};

#endif //IMA_TRAJECTORY_H
