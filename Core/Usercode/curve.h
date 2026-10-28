//
// Created by Administrator on 2026/10/28.
//

#ifndef TWO_LINK_LINKAGE_CURVE_H
#define TWO_LINK_LINKAGE_CURVE_H

// 变速曲线类型
enum CurveType
{
    Linear = 0,       // 1. 线性：速度恒定
    Cosine = 1,       // 2. 余弦：两端慢，中间快
    SmoothStep = 2,   // 3. 三次平滑：两端速度为零
    SmootherStep = 3, // 4. 五次平滑：两端加速度也为零
    Power = 4,        // 5. 幂函数：可调节减速强度
    Sine = 5          // 6. 正弦：两端慢，中间快
};

float apply_curve(float t, CurveType curve_type);

#endif //TWO_LINK_LINKAGE_CURVE_H
