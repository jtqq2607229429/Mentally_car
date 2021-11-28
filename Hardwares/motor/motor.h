//
// Created by JIANG on 2021/8/8.
//

#ifndef MY_MPU6050_MOTOR_H
#define MY_MPU6050_MOTOR_H
#include "main.h"

void motor1(int speed);
void motor2(int speed);
void stop();

void go_forward();
void go_back();
void turn_on(int dir);


#endif //MY_MPU6050_MOTOR_H
