//
// Created by JIANG on 2021/11/5.
//

#include "sensory_ability.h"
#include "usart.h"

uint8_t uartByte = 0;
uint8_t uartBuf[30];
extern int point_flag0, point_flag1, point_flag2, point_flag3;//第一点，第二点等各位置转向特点  1右转 2左转 3直行


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == huart2.Instance) {
        static uint8_t state = 0;
        switch (state) {
            case 0:
                if (uartByte == '(') {
                    state++;
                }
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                uartBuf[state - 1] = uartByte;
                state++;
                break;
            case 5:
                if ((uartByte - '0') == (uartBuf[0] + uartBuf[1] + uartBuf[2] + uartBuf[3] - 4 * '0')) {
                    point_flag0 = uartBuf[0] - '0';
                    point_flag1 = uartBuf[1] - '0';
                    point_flag2 = uartBuf[2] - '0';
                    point_flag3 = uartBuf[3] - '0';
                    state++;
                } else {
                    state = 0;
                }
                break;
            case 6:
                state = 0;
                break;
            default:
                state = 0;
                break;
        }
        UART_Start_Receive_IT(&huart2, (uint8_t *) &uartByte, 1);
    }
}
