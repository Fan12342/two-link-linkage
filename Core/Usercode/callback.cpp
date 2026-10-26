//
// Created by Administrator on 2026/10/24.
//

#include "../Usercode/can_user.h"
#include "two_link_linkage.h"

PID ppid_center = PID(15.0f, 0.0f, 55.0f, 0.1f, 120.0f, 0.5f);
PID spid_center = PID(0.6f, 0.0f, 0.05f, 0.0f, 10.0f, 0.1f);

PID ppid_out = PID(15.0f, 0.0f, 55.0f, 0.1f, 120.0f, 0.5f);
PID spid_out = PID(0.6f, 0.0f, 0.05f, 0.0f, 10.0f, 0.1f);

TwoLinkLinkage two_link = TwoLinkLinkage(1, 2, ppid_center, spid_center, ppid_out, spid_out);

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef* hcan)
{
    if (hcan->Instance == CAN1)
    {
        uint8_t data[8];
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, data) != HAL_OK)
            return;

        if (rx_header.IDE == CAN_ID_STD && rx_header.RTR == CAN_RTR_DATA && rx_header.DLC == 8)
        {
            two_link.can_callback(data, rx_header.StdId);
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim->Instance == TIM6)
    {
        // 记录距上次调用用时
        static uint32_t last_tick = 0;
        uint32_t tick = HAL_GetTick();
        uint32_t dt_ms;
        if (last_tick == 0)
            dt_ms = 10U;
        else
            dt_ms = tick - last_tick;
        last_tick = tick;

        // 更新控制数据
        two_link.update(dt_ms);

        // 发送数据
        if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0)
        {
            uint8_t* motor_data = two_link.get_motor_data();
            HAL_CAN_AddTxMessage(&hcan1, &tx_header, motor_data, &can_tx_mailbox);
        }
    }
}
