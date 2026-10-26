//
// Created by Administrator on 2026/10/24.
//

#ifndef TWO_LINK_LINKAGE_TWO_LINK_LINKAGE_H
#define TWO_LINK_LINKAGE_TWO_LINK_LINKAGE_H

#include "motor.h"
#include "TrajectorySquare.h"

class TwoLinkLinkage
{
public:
    TwoLinkLinkage(uint8_t motor_id_center, uint8_t motor_id_out, PID ppid_center, PID spid_center, PID ppid_out,
                   PID spid_out) : motor_center_(motor_id_center, ppid_center, spid_center),
                                   motor_out_(motor_id_out, ppid_out, spid_out), trajectory_(4000U)
    {
    }

    void can_callback(uint8_t* data, uint32_t stdid);
    uint8_t* get_motor_data();
    void update(uint32_t tick);

    float angle1, angle2; // 测试用

private:
    Motor_3508 motor_center_;
    Motor_3508 motor_out_;
    uint8_t tx_data_[8] = {};
    TrajectorySquare trajectory_;
};

#endif //TWO_LINK_LINKAGE_TWO_LINK_LINKAGE_H
