
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
#include "exe_op.h"
#include "flags.h"
#include "music.h"
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

    oi_init(sensor_data);
    IR_init();
    lcd_init();
    gpio_pb5_init();
    timer1_init();
    button_init();
    ping_gpioInit();
    timer_3_init();
    init_flags(sensor_data);


    uart_init();

    int success = WiFi_start("password1234");

}


int main(void)
{
    char c = NULL;
    flags* flag_data = getFlags();
    oi_t *sensor_data = oi_alloc();
    init_all(sensor_data);

    move_stop(sensor_data);

    wifi_continue();

    //load_songs();


    while(1)
    {
        check_flags();

        if(!readLCharRead())
        {//enters if the last character has not been acted on

            if(!readLCharRead())
            {
              c = uart_receive_last();
            }
            else
            {
              c = NULL;
            }

            if(c != NULL)
            {
              exe_op((op_cmds) c, sensor_data);
            }
        }

    }
}
