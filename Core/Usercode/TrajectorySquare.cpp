//
// Created by Administrator on 2026/10/23.
//

#include "TrajectorySquare.h"

static inline float linear(float x, float y, float k)
{
    return x * (1 - k) + y * k;
}

void TrajectorySquare::tick_to_point(float tick, PointData* point)
{
    // while 是为了防止 tick 超出 samples_
    while (true)
    {
        if (tick < samples_quarter_)
        {
            point->x = linear(-square_len_half_, square_len_half_, tick / samples_quarter_);
            point->y = square_len_half_;
        }
        else if (tick < samples_quarter_ * 2.0f)
        {
            point->x = square_len_half_;
            point->y = linear(square_len_half_, -square_len_half_, tick / samples_quarter_ - 1.0f);
        }
        else if (tick < samples_quarter_ * 3.0f)
        {
            point->x = linear(square_len_half_, -square_len_half_, tick / samples_quarter_ - 2.0f);
            point->y = -square_len_half_;
        }
        else if (tick < samples_quarter_ * 4.0f)
        {
            point->x = -square_len_half_;
            point->y = linear(-square_len_half_, square_len_half_, tick / samples_quarter_ - 3.0f);
        }
        else
        {
            tick -= samples_quarter_ * 4.0f;
            continue;
        }
        // 若没有进入 else 就 break
        break;
    }
}
