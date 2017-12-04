/*
 * exe_op.h
 *
 *  Created on: Dec 2, 2017
 *      Author: rtoepfer
 */

#ifndef EXE_OP_H_
#define EXE_OP_H_

typedef enum
{
    forward = 1,
    reverse = 2,
    left = 3,
    right = 4,
    scan = 121,
    stop = 6,
    song1 = 7, //backup beep
    song2 = 8, //rick_roll
    song3 = 9,
    song4 = 10,

} op_cmds;

#define DRIVE_SPEED 100
#define TURN_SPEED 200
#define TURN_CALIBRATION 1.045 // for cyBot-5
static oi_t* sensor_data;
void exe_op(op_cmds dir, oi_t* sensor_data);

#endif /* EXE_OP_H_ */
