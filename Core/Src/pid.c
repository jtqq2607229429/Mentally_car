//
// Created by JIANG on 2021/11/4.
//

#include "pid.h"

PID_struct forward_PID;
PID_struct back_PID;


void PID_Init(PID_struct *PID,float kp,float ki,float kd)//初始化PID结构体参数
{
    PID->err = 0;    //当前误差
    PID->err_last = 0;   //前一次误差
    PID->integral = 0;  //累计错误
    PID->Kp = kp;
    PID->Ki = ki;
    PID->Kd = kd;
    PID->out = 0;
}

float PID_calc(PID_struct *PID,float e)
{
    PID->err =e;
    PID->integral += PID->err;
    if(PID->integral >= 100)
        PID->integral = 100;
    if(PID->integral <= -100)
        PID->integral = -100;
    if(PID->err>=-1&& PID->err<=1)
        PID->integral = 0;

    PID->out = PID->Kp * PID->err +
               PID->Ki * PID->integral +
               PID->Kd *( PID->err - PID->err_last );
    PID->err_last = PID->err;

    return PID->out;
}

