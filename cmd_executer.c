//Command Executer
//CPRE_288
//author: Christopher Caldwell

#include <stdio.h>
#include "cmd_executer.h"
#include "objectcounter.h"
#include "open_interface.h"
#include "movement.h"

oi_t* sensor_data;

void exe_init(oi_t* sensor_data_arg){
    sensor_data = sensor_data_arg;
}

void exe_scan(){
    sweep_and_send();
}


void exe_move(char dir, char speed){ //dir == 0 => forward, dir == 1 => reverse

    int dist_c = 50; //cm

    if(dir == 0)
        {
            move_mm_at_speed(dist_c, speed, sensor_data); //void move_back_mm_at_speed(int cm, int speed, oi_t* sensor_data)
        }
    else if(dir == 1)
        {
            move_back_mm_at_speed(dist_c, speed, sensor_data);
        }
}


void exe_turn(char dir, char degree) //dir == 0 => right, dir == 1 => left
{
    if(dir == 0)
    {
        turn_right(degree, sensor_data);
    }
    else if(dir == 1)
    {
        turn_left(degree, sensor_data);
    }
}
