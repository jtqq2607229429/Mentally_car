//
// Created by JIANG on 2021/11/4.
//

#include "tracking.h"
//#include "adc.h"
#include "stdio.h"
#include "motor.h"
#include "gpio.h"

int GRAY1_f, GRAY2_f, GRAY3_f, GRAY4_f, GRAY5_f, GRAY6_f, GRAY7_f, GRAY8_f;
uint8_t gary_flag = 0;
float error_all;
int GRAY_f[10];
int stop_flag1 = 0,stop_flag2 = 0;

float error_q = 0, error_h = 0;

void A_D() {


//    uint16_t adcsum[8] = {0};
//    for (uint8_t j = 0; j < 8; j++) {
//        HAL_ADC_Start(&hadc1);
//        HAL_ADC_PollForConversion(&hadc1, 0xff);
//        if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
//            adcsum[j] += HAL_ADC_GetValue(&hadc1);
//        }
//    }
//
//    if (adcsum[0] < 3500) {
//        GRAY1_f = 1;
//    } else { GRAY1_f = 0; }
//
//    if (adcsum[1] < 3500) {
//        GRAY2_f = 1;
//    } else { GRAY2_f = 0; }
//
//    if (adcsum[2] < 3500) {
//        GRAY3_f = 1;
//    } else { GRAY3_f = 0; }
//
//    if (adcsum[3] < 3500) {
//        GRAY4_f = 1;
//    } else { GRAY4_f = 0; }
//
//    if (adcsum[4] < 3500) {
//        GRAY5_f = 1;
//    } else { GRAY5_f = 0; }
//
//    if (adcsum[5] < 3500) {
//        GRAY6_f = 1;
//    } else { GRAY6_f = 0; }
//
//    if (adcsum[6] < 3500) {
//        GRAY7_f = 1;
//    } else { GRAY7_f = 0; }
//
//    if (adcsum[7] < 3500) {
//        GRAY8_f = 1;
//    } else { GRAY8_f = 0; }       //adc转数字
//
////
//    printf("adcsum[0]:%d  adcsum[1]:%d  adcsum[2]:%d "
//           "adcsum[3]:%d  adcsum[4]:%d  adcsum[5]:%d "
//           "adcsum[6]:%d  adcsum[7]:%d   \r\n"
//           ,adcsum[0],adcsum[1],adcsum[2],adcsum[3]
//           ,adcsum[4],adcsum[5],adcsum[6],adcsum[7]);

}

void get_nowgray() {
    if (gary_flag == 0) {
        for (uint16_t i = 0; i < 8; i++) {
            GRAY_f[i] = 0;
//            GRAY_h[i]=0;
        }
        stop_flag1 =0;
        stop_flag2 =0;
    }

    gary_flag++;

    GRAY_f[0] += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
    GRAY_f[1] += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
    GRAY_f[2] += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
    GRAY_f[3] += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
    GRAY_f[4] += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);

    GRAY_f[5] += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
    GRAY_f[6] += HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    GRAY_f[7] += HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_11);
    GRAY_f[8] += HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13);
    GRAY_f[9] += HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13); //车前

    stop_flag1 += HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_11);
    stop_flag2 += HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8);

//    printf("stop_flag1:%d   \r\n", stop_flag1);


    if (gary_flag == 5) {   //采集五次判断
        for (uint16_t i = 0; i < 10; i++) {
            if (GRAY_f[i] >= 3) {
                GRAY_f[i] = 1;
            } else GRAY_f[i] = 0;
        }
        if (stop_flag1 >= 3){
            stop_flag1 =1;
        }else  stop_flag1 =0;

        if (stop_flag2 >= 3){
            stop_flag2 =1;
        }else  stop_flag2 =0;

        printf("stop_flag1:%d   \r\n", stop_flag1);
    }


}

float get_error(char dirction) {
    if (GRAY_f[0] == 1 && GRAY_f[1] == 1 && GRAY_f[2] == 1 && GRAY_f[3] == 1 && GRAY_f[4] == 1)
        error_q = 0;
    else if (GRAY_f[0] == 0 && GRAY_f[1] == 0 && GRAY_f[2] == 1 && GRAY_f[3] == 0 && GRAY_f[4] == 0)
        error_q = 0;
    else if (GRAY_f[0] == 0 && GRAY_f[1] == 1 && GRAY_f[2] == 1 && GRAY_f[3] == 0 && GRAY_f[4] == 0)
        error_q = 1;
    else if (GRAY_f[0] == 0 && GRAY_f[1] == 1 && GRAY_f[2] == 0 && GRAY_f[3] == 0 && GRAY_f[4] == 0)
        error_q = 2;
    else if (GRAY_f[0] == 1 && GRAY_f[1] == 1 && GRAY_f[2] == 0 && GRAY_f[3] == 0 && GRAY_f[4] == 0)
        error_q = 6;
    else if (GRAY_f[0] == 1 && GRAY_f[1] == 0 && GRAY_f[2] == 0 && GRAY_f[3] == 0 && GRAY_f[4] == 0)
        error_q = 8;
    else if (GRAY_f[0] == 0 && GRAY_f[1] == 0 && GRAY_f[2] == 1 && GRAY_f[3] == 1 && GRAY_f[4] == 0)
        error_q = -1;
    else if (GRAY_f[0] == 0 && GRAY_f[1] == 0 && GRAY_f[2] == 0 && GRAY_f[3] == 1 && GRAY_f[4] == 0)
        error_q = -2;
    else if (GRAY_f[0] == 0 && GRAY_f[1] == 0 && GRAY_f[2] == 0 && GRAY_f[3] == 1 && GRAY_f[4] == 1)
        error_q = -6;
    else if (GRAY_f[0] == 0 && GRAY_f[1] == 0 && GRAY_f[2] == 0 && GRAY_f[3] == 0 && GRAY_f[4] == 1)
        error_q = -8;

//error_hou[5]={-3,-1,0,1,3};
    if (GRAY_f[5] == 1 && GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 1 && GRAY_f[9] == 1)
        error_h = 0;
    else if (GRAY_f[5] == 0 && GRAY_f[6] == 0 && GRAY_f[7] == 1 && GRAY_f[8] == 0 && GRAY_f[9] == 0)
        error_h = 0;
    else if (GRAY_f[5] == 0 && GRAY_f[6] == 1 && GRAY_f[7] == 1 && GRAY_f[8] == 0 && GRAY_f[9] == 0)
        error_h = 2;
    else if (GRAY_f[5] == 0 && GRAY_f[6] == 1 && GRAY_f[7] == 0 && GRAY_f[8] == 0 && GRAY_f[9] == 0)
        error_h = 4;
    else if (GRAY_f[5] == 1 && GRAY_f[6] == 1 && GRAY_f[7] == 0 && GRAY_f[8] == 0 && GRAY_f[9] == 0)
        error_h = 6;
    else if (GRAY_f[5] == 1 && GRAY_f[6] == 0 && GRAY_f[7] == 0 && GRAY_f[8] == 0 && GRAY_f[9] == 0)
        error_h = 8;
    else if (GRAY_f[5] == 0 && GRAY_f[6] == 0 && GRAY_f[7] == 1 && GRAY_f[8] == 1 && GRAY_f[9] == 0)
        error_h = -2;
    else if (GRAY_f[5] == 0 && GRAY_f[6] == 0 && GRAY_f[7] == 0 && GRAY_f[8] == 1 && GRAY_f[9] == 0)
        error_h = -4;
    else if (GRAY_f[5] == 0 && GRAY_f[6] == 0 && GRAY_f[7] == 0 && GRAY_f[8] == 1 && GRAY_f[9] == 1)
        error_h = -6;
    else if (GRAY_f[5] == 0 && GRAY_f[6] == 0 && GRAY_f[7] == 0 && GRAY_f[8] == 0 && GRAY_f[9] == 1)
        error_h = -8;

    if(GRAY_f[5] == 0 && GRAY_f[6] == 0 && GRAY_f[7] == 0 && GRAY_f[8] == 0 && GRAY_f[9] == 0&&
        GRAY_f[0] == 0 && GRAY_f[1] == 0 && GRAY_f[2] == 0 && GRAY_f[3] == 0 && GRAY_f[4] == 0)
        return 100;

    if (dirction == 'h') {
        if ((error_q * error_h) < 0)
            error_all = error_q - (float) 0.3 * error_h;
        if ((error_q * error_h) >= 0)
            error_all = error_q + (float) 0.5 * error_h;
    } else {
        if ((error_q * error_h) < 0)
            error_all = error_h - (float) 0.3 * error_q;
        if ((error_q * error_h) >= 0)
            error_all = error_h + (float) 0.5 * error_q;
    }
    return error_all;
}





