//
// Created by Administrator on 2026/10/28.
//

#include "curve.h"

#include <cmath>
#include <algorithm>

// 将 0~1 映射为 0~1
float apply_curve(float t, CurveType curve_type)
{
    constexpr float PI = 3.14159265358979323846f;

    switch (curve_type)
    {
    case CurveType::Linear:
        return t;

    case CurveType::Cosine:
        return 0.5f * (1.0f - std::cos(PI * t));

    case CurveType::SmoothStep:
        return t * t * (3.0f - 2.0f * t);

    case CurveType::SmootherStep:
        return t * t * t * (t * (6.0f * t - 15.0f) + 10.0f);

    case CurveType::Power:
        {
            constexpr float P = 2.0f;
            if (t < 0.5f)
                return 0.5f * std::pow(2.0f * t, P);
            return 1.0f - 0.5f * std::pow(2.0f * (1.0f - t), P);
        }

    case CurveType::Sine:
        return t - std::sin(2.0f * PI * t) / (2.0f * PI);

    default:
        return t;
    }
}
