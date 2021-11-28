//
// Created by JIANG on 2021/11/4.
//

#include <tim.h>
#include "tim_irq.h"
#include "tracking.h"
#include "pid.h"
#include "motor.h"
#include "stdio.h"
#include "task.h"

int mode = 0;
extern int GRAY_f[10];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim1.Instance) {
        get_nowgray();
        if (gary_flag == 5) {
//            task1();
            all_task();
//            go_forward();
//            go_back();
//            turn_on(0);
//            motor1(3000);  //左轮 前进

            if (mode == 1) {
                go_forward();
            } else if (mode == 2) {

            }else if (mode == 3){
                go_back();
            }
            gary_flag = 0;
        }  //计算
    }
    HAL_TIM_Base_Start_IT(htim);
}