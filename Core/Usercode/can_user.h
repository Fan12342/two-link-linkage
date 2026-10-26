//
// Created by Administrator on 2026/10/24.
//

#ifndef TWO_LINK_LINKAGE_CAN_H
#define TWO_LINK_LINKAGE_CAN_H

#include "can.h"

extern CAN_RxHeaderTypeDef rx_header;
extern CAN_TxHeaderTypeDef tx_header;
extern uint32_t can_tx_mailbox;
extern CAN_FilterTypeDef can_filter_config;

#endif //TWO_LINK_LINKAGE_CAN_H
