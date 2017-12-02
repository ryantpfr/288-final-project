
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
#include "open_interface.h"
#include "movement.h"
#include "uart.h"


void wifi_continue(){

    while(true){
        char recieved = uart_receive2();
        if(recieved == 'c'){
            break;
        }
    }

    transmit_str(CONNECTED);
}


void init_all(oi_t *sensor_data){
    IR_init();
    lcd_init();
    gpio_pb5_init();
    timer1_init();
    button_init();
    ping_gpioInit();
    timer_3_init();
    oi_init(sensor_data);
    uart_init();
    int success = WiFi_start("password1");

}


bool readSensors(oi_t *sensor_data){

    if( sensor_data->bumpLeft == 1){
        return true;
    }
    if( sensor_data->bumpRight == 1){
        return true;
    }

    return false;
}

int main(void)
{
    oi_t *sensor_data = oi_alloc();
    init_all(sensor_data);

    wifi_continue();

    while(true){

        if(!readLCharRead()){//enters if the last character has not been acted on
            char c = uart_receive_last();
            exe_op((op_cmds) c, sensor_data);
        }

    }


//    move_mm_at_speed_until_collision(1000, 50,sensor_data);
//
//    timer_waitMillis(200);
//
//    move_mm_at_speed_until_collision(1000, 50,sensor_data);

    //move_at_speed(50,sensor_data);
//
//    lcd_printf("hello");
//
//    while(true){
//        lcd_printf("hello : %d",sensor_data->bumpRight);
//        move_stop();
//        if(readSensors(sensor_data) == true){
//            move_stop();
//            break;
//        }
//    }

    while(true);
}
