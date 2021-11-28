//
// Created by JIANG on 2021/11/5.
//

#include "task.h"
#include "motor.h"

int all_step = 2, step = 0, line_flag = 0, line_num, point_flag0 = 0, point_flag1 = 0, point_flag2 = 2, point_flag3 = 2;
extern int GRAY_f[10];
extern int stop_flag1, stop_flag2;
extern int mode;
uint8_t time = 0;
int delaytime = 0;
int turn_step = 0;
int turn_flag = 0, back_flag = 0, yao_flag = 0;

int mydelay(int time) {
    delaytime++;
    if (delaytime >= time)
        return 1;
    else
        return 0;
}

void time_reset() {
    time = 0;
    delaytime = 0;
}

//if (line_flag == 1) {
//if (GRAY_f[4] == 1 || GRAY_f[0] == 1) line_flag = 2;
//}
//if (line_flag == 2) {
//step++;
//line_flag = 0;
//line_num++;//数显一条
//}
void all_task() {
//    switch (step) {
//        case 0:
//            mode = 1;
//            if (GRAY_f[5] == 1 || GRAY_f[9] == 1) {//前一排测线
//                step++;
//            }
//            break;
//        case 1:
//            turn_on(2); break;
//    }
//}
    switch (step) {
        case 0:
            if (point_flag0 != 0) {
                step++;
            }
            break;
        case 1:
            if (!HAL_GPIO_ReadPin(yao_flag_GPIO_Port, yao_flag_Pin)) {
                step++;
            }
            break;
        case 2:
            mode = 1;  //直行
            step++;
            break;
        case 3:
            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) {//前一排测线
                step++;
            }
            break;
        case 4:
            if (point_flag0 != 3) {
                turn_on(point_flag0);  //转弯
                if (turn_flag == 1) {
                    HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
                    turn_flag = 0;
                    turn_step = 0;
                    step = 99;
                    back_flag = 1;
                }
            } else {
                if (GRAY_f[3] == 1 && GRAY_f[4] == 1 && GRAY_f[2] == 1) {//后一排测线
                    step++;
                    line_num = 1;
                }
            }
            break;
        case 5:
            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) {//前一排测线
                if (point_flag1 == 0) {
                    step = 500;
                } else { step++; }
            }
            break;
        case 6:
            if (point_flag1 != 3) {
                turn_on(point_flag1);
                if (turn_flag == 1) {
                    HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
                    turn_flag = 0;
                    turn_step = 0;
                    step = 109;                //第二个点回家
                    back_flag = 1;
                }
            } else {
                if (GRAY_f[1] == 1 && GRAY_f[2] == 1 && GRAY_f[3] == 1) {//后一排测线
                    step++;
                    line_num = 2;
                }
            }
            break;// if(GRAY_f[9] == 1) {all_step++; }    breakbreak;

        case 7:
            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) {//前一排测线  // 第三个点
                step++;
                line_num = 3;
            }
            break;

        case 8:
            turn_on(point_flag2);
            if (turn_flag == 1) {
                turn_flag = 0;
                turn_step = 0;
                step++;
            }
            break;
        case 9:
            turn_on(point_flag3);
            if (turn_flag == 1) {
                turn_step = 0;
                turn_flag = 0;
                step++;
            }
            break;
        case 10:
            if (HAL_GPIO_ReadPin(yao_flag_GPIO_Port, yao_flag_Pin)) {
                step++;
                HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
            }
            break;
        case 11:
            mode = 3;
            step++;
            break;
        case 12:
            if (GRAY_f[3] == 1 && GRAY_f[4] == 1 && GRAY_f[2] == 1) { step++; }
            break;
        case 13:
            if (GRAY_f[5] == 1 && GRAY_f[6] == 1 && GRAY_f[7] == 1) { step++; }
            break;
        case 14:
            mode = 2;
            motor1(4000);
            motor2(4000);
            time_reset();
            step++;
        case 15:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                step++;
            }
            break;// if(GRAY_f[9] == 1) {all_step++; }    break;
        case 16:
            turn_on(2);
            if (turn_flag == 1) {
                turn_step = 0;
                turn_flag = 0;
                step++;
            }
            break;
        case 17:
            mode = 1;
            step++;
            break;
        case 18:
            if (GRAY_f[7] == 1 && GRAY_f[8] == 1 && GRAY_f[9] == 1) { step++; }
            break;
        case 19:
            motor1(-4000);
            motor2(-4000);
            time_reset();
            step++;
            break;
        case 20:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                step++;
                turn_step = 0;
            }
            break;
        case 21:
            turn_on(1);
            if (turn_flag == 1) {
                turn_flag = 0;
                turn_step = 0;
                step++;
            }
            break;
        case 22:
            mode = 1;
            step++;
            break;
        case 23:
            if (GRAY_f[1] == 1 && GRAY_f[2] == 1 && GRAY_f[3] == 1) {
                step++;
            }
            break;
        case 24:
            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) {
                step++;
            }
            break;
        case 25:
            if (GRAY_f[1] == 1 && GRAY_f[2] == 1 && GRAY_f[3] == 1) {
                step++;
            }
            break;
        case 26:
            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) {
                step++;
            }
            break;
        case 27:
            if (stop_flag1 == 1 || stop_flag2 == 1) {
                mode = 2;
                step++;
            }
        case 28:
            motor1(-5000);
            motor2(-5000);
            time_reset();
            step++;
            break;
        case 29:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                step++;
            }
            break;
        case 30:
            mode = 2;
            stop();
            HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
            break; //停止

            //        case 17:
//            if (point_flag2 == 1) {
//                point_flag2 = 2;
//            } else if (point_flag2 == 2) { point_flag2 = 1; }
//            step++;
//            break;
//        case 18:
//                turn_on(1);
//            if (turn_flag == 1) {
//                turn_flag = 0;
//                step++;
//            }
//            break;
//        case 19:
//            mode = 1;
//            if (GRAY_f[3] == 1 && GRAY_f[4] == 1 && GRAY_f[2] == 1) { step++; }
//            break;
//
//        case 20:
//            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) { step++; }
//            break;
//        case 21:
//            if (GRAY_f[3] == 1 && GRAY_f[4] == 1 && GRAY_f[2] == 1) { step++; }
//            break;
//
//        case 22:
//            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) { step++; }
//            break;
//        case 23:
//            if (stop_flag1 == 1 || stop_flag2 == 1) {
//                mode = 2;
//                step++;
//            }
//            break;
//        case 24:
//            motor1(-5000);
//            motor2(-5000);
//            time_reset();
//            step++;
//            break;
//        case 25:
//            time = mydelay(20);
//            if (time == 1) {
//                time_reset();
//                step++;
//            }
//            break;
//        case 26:
//            mode = 2;
//            stop();
//            step++;
//            break; //停止
//
//        case 27:
//            mode = 3;
//            step++;
//            break;

        case 99:
            if (HAL_GPIO_ReadPin(yao_flag_GPIO_Port, yao_flag_Pin)) {
                step++;
                HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
            }
            break;
        case 100:
            mode = 3;
            step++;
            break;
        case 101:
            if (GRAY_f[0] == 1 || GRAY_f[4] == 1) { step++; }
            break;
        case 102:
            if (GRAY_f[5] == 1 || GRAY_f[9] == 1) { step++; }
            break;
        case 103:
            turn_on(point_flag0);
            if (turn_flag == 1) {
                HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
                turn_flag = 0;
                turn_step = 0;
                step++;
            }
            break;                   //第一点回家

        case 104:
            stop();
            break;

        case 109:
            if (HAL_GPIO_ReadPin(yao_flag_GPIO_Port, yao_flag_Pin)) {
                step++;
                HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
            }
            break;
        case 110:
            mode = 3;
            step++;
            break;
        case 111:
            if (GRAY_f[1] == 1 && GRAY_f[2] == 1 && GRAY_f[3] == 1) { step++; }
            break;
        case 112:
            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) { step++; }
            break;
        case 113:
            turn_on(point_flag1);
            if (turn_flag == 1) {
                step++;
                mode = 1;
            }
            break;                   //第二点回家
        case 114:
            if (GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1) { step++; }
            break;
        case 115:
            if (GRAY_f[1] == 1 && GRAY_f[2] == 1 && GRAY_f[3] == 1) { step++; }
            break;
        case 116:
            if (stop_flag1 == 1 || stop_flag2 == 1) {
                mode = 2;
                step++;
            }
            break;
        case 117:
            motor1(-5000);
            motor2(-5000);
            time_reset();
            step++;
            break;
        case 118:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                step++;
            }
            break;
        case 119:
            mode = 2;
            stop();
            HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
            break; //停止


        case 500:
            mode = 3;
            step++;
            break;
        case 501:
            time = mydelay(400);
            if (time == 1) {
                time_reset();
                step++;
            }
            break;
        case 502:
            mode = 2;
            stop();
            step++;
            break;
        case 503:
            time = mydelay(700);
            if (time == 1) {
                time_reset();
                mode = 1;
                step = 5;
            }
            break;
//        case 504: if( point_flag1 == 0){
//            step = 5 ;
//        } else{
//            step = 6;
//            }break;
    }

}

//           if(point_flag0 != 3){
//               turn_on(point_flag0);
//           }
//            break;       //线检测
//        case 4:
//            if (GRAY_f[5] == 1 || GRAY_f[9] == 1) {
//                step++; //前一排已经测到线
//                line_flag = 1;  //前一排已经测到线
//            }
//            break;
//        case 5:
//            if (point_flag1 != 3) {
//                mode = 2;
//                motor1(-5000);
//                motor2(-5000);
//                time_reset();
//                step++;
//            } else {  //直行
//                step++;
//            }
//            break;
//        case 6:
//            if (point_flag1 != 3) {
//                turn_on(point_flag1);
//            } else { step++; }
//            break;
//        case 7:
//                if (line_flag == 1) { //后一派看到线
//                    if (GRAY_f[4] == 1 || GRAY_f[0] == 1)
//                        step++;
//                    line_flag = 0;
//                    line_num++;//数显一条
//                }
//            break;
//        case 8:
//                if (GRAY_f[5] == 1 || GRAY_f[9] == 1) {
//                    step++; //前一排已经测到线
//                    line_flag = 1;  //前一排已经测到线
//                }
//            break;
//        case 9:if(point_flag2!=3){
//
//                turn_on(point_flag2);
//        }
//
//        case 10:
//            if (point_flag1 != 3) { //判断是不是拐弯
//                time = mydelay(20);
//                if (time == 1) {
//                    time_reset();
//                    step++;
//                }
//                break;// if(GRAY_f[9] == 1) {all_step++; }    break;
//                case 11:
//                    stop();
//                break; //等待取药
//            }
//
//    }
//}


void turn(int dir) {
    if (dir == 1) {
        motor1(4000);//右转
        motor2(0);
    } else {
        motor1(0);//右转
        motor2(4000);
    }
}

void turn_on(int dir) {   //turn_on
    switch (turn_step) {
        case 0:
            mode = 2;
            if (back_flag == 1) {
                motor1(4000);
                motor2(4000);
            } else {
                motor1(-4000);
                motor2(-4000);
            }
            time_reset();
            turn_step++;
            break;
        case 1:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                turn_step++;
            }
            break;
        case 2:
            turn(dir);
            turn_step++;
            break;
        case 3:
            time = mydelay(280);
            if (time == 1) {
                time_reset();
                turn_step++;
            }
            break;
        case 4:
            mode = 1;
            if (stop_flag1 == 1 || stop_flag2 == 1) {
                mode = 2;
                turn_step++;
            }
            break;
        case 5:
            if (back_flag == 1) {
                motor1(4000);
                motor2(4000);
            } else {
                motor1(-4000);
                motor2(-4000);
            }
            time_reset();
            turn_step++;
            break;
        case 6:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                turn_step++;
            }
            break;
        case 7:
            mode = 2;
            stop();
            turn_flag = 1;
            break; //停止
    }
}


void task1() {
    switch (step) {
//        case 0:   break;//识图
//        case 1:  break;// if(){} break; //识药
        case 2:
            mode = 1;
            step++;
            break; //直走
        case 3:
            if (stop_flag1 == 1 || stop_flag2 == 1) {  //前有线
                mode = 2;
                step++;
            }
            break;
////                  if(line_flag ==1 ){
////                      if (GRAY_f[4] == 1 || GRAY_f[0] == 1) line_flag = 2;
////                  }
////                  if(line_flag == 2){
////                  }break;       //线检测
        case 4:
            motor1(-5000);
            motor2(-5000);
            time_reset();
            step++;
            break;
        case 5:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                step++;
            }
            break;// if(GRAY_f[9] == 1) {all_step++; }    break;
        case 6:
            turn(1);
            step++;
            break; //0和1
        case 7:
            time = mydelay(370);
            if (time == 1) {
                time_reset();
                step++;
            }
            break;// if(GRAY_f[9] == 1) {all_step++; }    break;

        case 8:
            mode = 1;
            if (stop_flag1 == 1 || stop_flag2 == 1) {
                mode = 2;
                step++;
            }
            break;
        case 9:
            motor1(-5000);
            motor2(-5000);
            time_reset();
            step++;
            break;
        case 10:
            time = mydelay(10);
            if (time == 1) {
                time_reset();
                step++;
            }
            break;// if(GRAY_f[9] == 1) {all_step++; }    break;
        case 11:
            stop();
            break; //等待取药

////                mode = 3; all_step++;}
////                case 7:break;
//
    }
}
