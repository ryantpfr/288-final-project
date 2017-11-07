/*
 * ping.c
 *
 *  Created on: Oct 12, 2017
 *      Author: rtoepfer
 */

#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "ping.h"
#include "driverlib/interrupt.h"
#define P_3 0x8
#define LOAD_INTERVAL 0xFFFF


int gpio_read(){
    return (GPIO_PORTB_DIR_R & P_3) >> 3;
}

void gpio_set_out(){
    GPIO_PORTB_DIR_R |= P_3;
}

void gpio_set_in(){
    GPIO_PORTB_DIR_R &= ~P_3;
}

void ping_gpioInit(){
    SYSCTL_RCGCGPIO_R |= 0x2;
    GPIO_PORTB_DEN_R |= P_3;

    GPIO_PORTB_PCTL_R &= ~0x0000F000;
    GPIO_PORTB_PCTL_R |= 0x7000;

    GPIO_PORTB_AFSEL_R |= P_3;
}

void gpio_ping_on(){
    GPIO_PORTB_DATA_R |= P_3;
}

void gpio_ping_off(){
    GPIO_PORTB_DATA_R &= ~P_3;
}

void gpio_ping_micros(int micros){
    gpio_set_out();
        GPIO_PORTB_AFSEL_R &= ~P_3;
            gpio_ping_on();
                timer_waitMicros(micros);
            gpio_ping_off();
        GPIO_PORTB_AFSEL_R |= P_3;
    gpio_set_in();
}




//////////////////////////////////////timer stuff/////////////////////////////////
#define P_B 0x1

volatile uint32_t current_distance = 0;
volatile uint32_t last_distance = 0;
volatile bool current_read = false;

bool aaaa(){
    return current_read;
}


uint32_t read_ping_when_done(){
     while(current_read);
     current_read = true;
     return read_distance();
}

uint32_t delta_with_overflow(){
    if(current_distance > last_distance){
        return current_distance-last_distance;
    }else{
        return current_distance-last_distance + LOAD_INTERVAL;
    }
}

uint32_t read_distance(){
    uint32_t delta = delta_with_overflow();
    current_read = true;
    return delta/92.55-8.849;
}

void input_capture_interrupt(){


    TIMER3_ICR_R |= 0x400;

    int data = gpio_read();

    last_distance = current_distance;
    current_distance = TIMER3_TBR_R;

    if(!data){
        current_read = false;
    }
}

void timer_3_init(){

    //enable timer 3
    SYSCTL_RCGCTIMER_R |=  0x8;

    //disable timer 3b
    TIMER3_CTL_R &= 0xC00;

    //config
    TIMER3_CFG_R = 0x4;//0x00;

    //timer b mode register (input capture, count up)
    TIMER3_TBMR_R = 0x17;

    //timer b interval load
    TIMER3_TBILR_R = LOAD_INTERVAL;

    //clear timeout flag
    TIMER3_ICR_R |= 0x400;

    //interupt mask everything we don't need
    TIMER3_IMR_R = 0x400;

    //enable timer 3b
    TIMER3_CTL_R |= 0xD00;


    NVIC_EN1_R |= 0x10;  //pg 105

    IntRegister(INT_TIMER3B,input_capture_interrupt);
    IntMasterEnable();
}

