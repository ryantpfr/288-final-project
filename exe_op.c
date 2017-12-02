//Command Parser and Command Executer
//CPRE_288
//@author Christopher Caldwell

#include <stdio.h>
#include "cmd_executer.h"
include "objectcounter.h"
#include "open_interface.h"
#include "movement.h"

oi_t* sensor_data;

enum op_cmds
{
    forward,
    reverse,
    left,
    right,
    scan,
    song,
    stop
};

/*
Below is the new exe_move that handles all movement and scanning.
*/

void exe_op(op_cmds dir, oi_t* sensor_data)
{
    switch (dir)
    {
    case forward:
        oi_setWheels(DRIVE_SPEED, DRIVE_SPEED);
        break;
    case reverse:
        oi_setWheels(-DRIVE_SPEED, -DRIVE_SPEED);
        break;
    case right:
        oi_setWheels(-TURN_SPEED, TURN_SPEED);
        break;
    case left:
        oi_setWheels(TURN_SPEED, -TURN_SPEED);
        break;
    case scan:
        sweep_and_send();
        break;
    case song:
        //TODO
        break;
    default: //stop
        oi_setWheels(0,0);
        break;
    }
}

}
