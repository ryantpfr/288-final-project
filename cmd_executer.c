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


void exe_move(char speed)  //forward/reverse : <cmd> <speed> : ex. cmds: 0 100 or 0 -100
{
    move_straight(speed, sensor_data);
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
