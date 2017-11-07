
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


    sweep_and_send();
}
