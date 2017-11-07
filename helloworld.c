
#include "timer.h"
#include <stdbool.h>
#include "lcd.h"
#include "button.h"
#include "servo.h"
#include "uart.h"
#include "wifi.h"
#include "banner.h"
#include "ir.h"
#include "ping2.h"
#include "objectcounter.h"

void reset_direction(int* direction, int* degrees){
    if(*degrees >= 90){
        *direction = -1;
    }else if(*degrees <= -90){
        *direction = 1;
    }

}

void wifi_continue(){

    while(true){
        char recieved = uart_receive2();
        if(recieved == 'c'){
            break;
        }
    }

    transmit_str(CONNECTED);
}


int main(void)
{
    IR_init();
    lcd_init();
    gpio_pb5_init();
    timer1_init();
    button_init();
    ping_gpioInit();
    timer_3_init();

    servo_set_degrees(-90);

    lcd_printf("Not Connected");
    WiFi_start("password1");
    wifi_continue();


    REMOVE : 1;

    int direction = 1;

    int degrees = -90;

    while(degrees != 90 || false){

       gpio_ping_micros(10);

       degrees += direction*2;
       servo_set_degrees(degrees);
       reset_direction(&direction,&degrees);

       int irData = IR_ReadMM();
       uint32_t pingData = read_ping_when_done();

       counter_write(degrees,irData,pingData);

       char message[20];
       sprintf(message,"%d : %d : %d\n%d",degrees, irData , pingData,getObjCount());

       lcd_printf(message);

       //transmit_str(message);

    }

    lcd_printf("minimum size is %d",getMinSize());
    servo_set_degrees(getMinDegrees());
    timer_waitMillis(800);

    while(button_getButton() == 0);
    servo_set_degrees(-90);
    goto REMOVE;

}
