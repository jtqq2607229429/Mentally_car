//
// Created by JIANG on 2021/8/8.
//

#include "motor.h"
#include "tim.h"
#include "tracking.h"
#include "pid.h"
#include "task.h"


void motor1(int speed) {
    if (speed >= 8099) {
        speed = 8099;
    } else if (speed <= -8099) {
        speed = -8099;
    }                //限幅

    if (speed > 0) {

        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
    } else {
        speed = -speed;
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
    }

}

void motor2(int speed) {
    if (speed >= 8099) {
        speed = 8099;
    } else if (speed <= -8099) {
        speed = -8099;
    }                //限幅

    if (speed < 0) {
        speed = -speed;
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, speed);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
    } else {

        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, speed);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
    }

}

int out1 = 0, out2 = 0, out = 0;
float e;

void go_forward() {
    e = (float) get_error('q');
    out = (int) PID_calc(&forward_PID, e);

    out1 = 3700 - out;
    out2 = 3700 + out;

    if (out1 >= 9000) out1 = 9000;
    if (out2 >= 9000) out2 = 9000;
    if (out1 <= 2000) out1 = 2000;
    if (out2 <= 2000) out2 = 2000;


    if (e == 100) { stop(); }
    else {
        motor1(out1);
        motor2(out2);
    }

}

void go_back() {
    e = (float) get_error('h');
    out = (int) PID_calc(&forward_PID, e);

    out1 = 3200 + out;
    out2 = 3200 - out;

    if (out1 >= 9000) out1 = 9000;
    if (out2 >= 9000) out2 = 9000;
    if (out1 <= 2000) out1 = 2000;
    if (out2 <= 2000) out2 = 2000;


    if (e == 100) { stop(); }
    else {
        motor1(-out1);
        motor2(-out2);
    }
}


void stop() {
    motor2(0);
    motor1(0);
}

//void turn(int angel)
//{
//    if (angel >= 300) {
//        angel = 300;
//    } else if (angel <= -300) {
//        angel = -300;
//    }                //限幅
//
//    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 1500+angel);
//    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, 1500-angel);
//}
//

//void get_speed()
//{
//
//}
