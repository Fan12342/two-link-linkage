//
// Created by Administrator on 2026/10/23.
//

#ifndef IMA_TRAJECTORYSQUARE_H
#define IMA_TRAJECTORYSQUARE_H

#include "TrajectoryFitter.h"

class TrajectorySquare : public TrajectoryFitter
{
public:
    // 长度单位统一为 mm
    TrajectorySquare(uint32_t samples) : TrajectoryFitter(samples, 100.0f, 100.0f), samples_(samples), samples_quarter_(static_cast<float>(samples) / 4.0f)
    {
    };

protected:
    uint32_t samples_;
    float samples_quarter_;
    float square_len_ = 200.0f;
    float square_len_half_ = square_len_ / 2.0f;

    void tick_to_point(float tick, PointData* point) override;
};

#endif //IMA_TRAJECTORYSQUARE_H
