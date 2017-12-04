/*
 * flags.h
 *
 *  Created on: Dec 2, 2017
 *      Author: rtoepfer
 */

#ifndef FLAGS_H_
#define FLAGS_H_

#include "open_interface.h"

//FIXME NEED TO HAVE CORRECT VALUES HERE
#define TARGET_MAX 1000
#define TARGET_MIN 500
#define BOUNDARY 1500

#define bumpR_f 0b0001
#define bumpL_f 0b0100
#define bumpF_f 0b0010
#define cliffL_s 0b1000
#define cliffFL_s 0b0100
#define cliffFR_s 0b0010
#define cliffR_s 0b0001

void check_boundary_f();
//flags get_flags();

typedef struct{
    char boundary_f;
    char bumpers_f;
    char cliff_f;
    char drop_f;
} flags;

void check_flags();
flags* getFlags();


#endif /* FLAGS_H_ */
