
#include <stdbool.h>
#include "timer.h"
#include <inc/tm4c123gh6pm.h>
#include "servo.h"



void gpio_pb5_init(){
    SYSCTL_RCGCGPIO_R |= 0x2;
    GPIO_PORTB_DIR_R |= 0x20; //output

    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R &= 0xFF0FFFFF;
    GPIO_PORTB_PCTL_R |= 0x00700000;

    GPIO_PORTB_DEN_R |= 0x20;
}



//uint32_t pulse_period = ; // pulse period in cycles

void timer1_init()//change to 1
{
//***set GPIO PB5, turn on clk, alt. function, output, enable***
    SYSCTL_RCGCTIMER_R |= 0x2; //turn on clk for timer1
    TIMER1_CTL_R &= ~0x100; //disable timer to config
    TIMER1_CFG_R = 0x4; //set size of timer to 16

    TIMER1_TBMR_R = (0x2 | 0x8); //periodic and PWM enable

    TIMER1_TBILR_R = (CLOCK_LOAD & 0xFFFF); //lower 16 bits of the interval
    TIMER1_TBPR_R = (CLOCK_LOAD >> 16); //set the upper 8 bits of the interval
    TIMER1_TBMATCHR_R = ((CLOCK_LOAD-24000)  & 0xFFFF); // if you want to move servo to the middle
    TIMER1_TBPMR_R = ((CLOCK_LOAD-24000) >> 16);

    TIMER1_CTL_R |= 0x100; //enable timer


}

float servo_bound_to(float min,float max,float val){
    if(val > max){
        return max;
    }else if(val < min){
        return min;
    }else{
        return val;
    }
}

void servo_set_degrees(float degrees){//from -90 -> 90


    int matcherVal = CLOCK_MID - DEGREE_SCALE*degrees;

    TIMER1_TBMATCHR_R = (matcherVal & 0xFFFF); // if you want to move servo to the middle
    TIMER1_TBPMR_R = (matcherVal >> 16);

    timer_waitMillis(100);

}

void servo_set_degrees_scan(float degrees){//from -90 -> 90


    int matcherVal = CLOCK_MID - DEGREE_SCALE*degrees;

    TIMER1_TBMATCHR_R = (matcherVal & 0xFFFF); // if you want to move servo to the middle
    TIMER1_TBPMR_R = (matcherVal >> 16);

    timer_waitMillis(50);

}

void servo_set_degrees_bounded(float degrees){//from -90 -> 90

    degrees = servo_bound_to(-90.0,90.0,degrees);

    int matcherVal = CLOCK_MID - DEGREE_SCALE*degrees;
    //int matcherVal = CLOCK_LOAD - 35000;
    //int matcherVal = CLOCK_LOAD - 7500;

    TIMER1_TBMATCHR_R = (matcherVal & 0xFFFF); // if you want to move servo to the middle
    TIMER1_TBPMR_R = (matcherVal >> 16);

    timer_waitMillis(100);

}

void calibration_test(){
    int matcherVal = CLOCK_LOAD - 36000;
    //int matcherVal = CLOCK_LOAD - 7500;


    TIMER1_TBMATCHR_R = (matcherVal & 0xFFFF); // if you want to move servo to the middle
    TIMER1_TBPMR_R = (matcherVal >> 16);

}
