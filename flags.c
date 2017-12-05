//flags module
#include "flags.h"
#include <stdbool.h>
#include "uart.h"

char stop_flag = 0;
char cliff_f = 0;
char target_f = 0;

char bumpers_f = 0;

char boundary_f = 0;
char drop_f = 0;

static oi_t* sensor_data;
static flags* flag_data;

void check_flags();
char set_drop_f();
void check_cliff_sensors();
void check_bumpers_f();


void init_flags(oi_t* s_data){
    sensor_data = s_data;
}

void check_flags()
{
  oi_update(sensor_data);
  lcd_printf("L: %d, FL: %d,\nFR: %d, R: %d,\n Bl %d, Br %d", sensor_data->cliffLeftSignal, sensor_data->cliffFrontLeftSignal, sensor_data->cliffFrontRightSignal, sensor_data->cliffRightSignal,sensor_data->bumpLeft,sensor_data->bumpRight);

  check_angle();
  check_distance();
  //set_drop_f();
  check_cliff_sensors();
  check_bumpers_f();
  check_boundary_f();



}

void check_angle(){
    if(sensor_data->angle != 0){
        char angleData[] = {7,sensor_data->angle};
        transmit_str_num(angleData,2);
    }
}

void check_distance(){
    if(sensor_data->distance != 0){
        char distanceData[] = {9,sensor_data->distance};
        transmit_str_num(distanceData,2);
    }
}

char set_drop_f()
{
  lcd_printf("%d %d %d %d",sensor_data->wheelDropLeft,sensor_data->wheelDropRight,sensor_data->cliffFrontLeft,0);
  if((sensor_data->wheelDropLeft) || (sensor_data->wheelDropLeft))
  {
      int left_wheel = sensor_data->wheelDropLeft;
      int right_wheel = sensor_data->wheelDropRight;
      flag_data->drop_f = 1;
  }

  return flag_data->drop_f;
}

void check_cliff_sensors() //?? Not sure if this is correct ?? FIXME
{
//    //White line detect, any sensor greater than 2750
//    if ((sensor_data->cliffLeftSignal > 2750) || (sensor_data->cliffFrontLeftSignal> 2750) || (sensor_data->cliffFrontRightSignal > 2750) || (sensor_data->cliffRightSignal > 2750))
//    {
//        char numEncoding = 0;
//        if(sensor_data->cliffLeftSignal > 2750){
//            numEncoding |= 0x8;
//        }if(sensor_data->cliffFrontLeftSignal > 2750){
//            numEncoding |= 0x4;
//        }if(sensor_data->cliffFrontRightSignal > 2750){
//            numEncoding |= 0x2;
//        }if(sensor_data->cliffRightSignal > 2750){
//            numEncoding |= 0x1;
//        }
//
//        char startCommand[] = {6,numEncoding,0}; //final value of 0 represents boundary
//        transmit_str_num(startCommand,1);
//    }

    static bool lCliffSent = false;
    static bool flCliffSent = false;
    static bool frCliffSent = false;
    static bool rCliffSent = false;

    if(sensor_data->cliffLeftSignal <= CLIFF_EDGE){
        move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!lCliffSent){
            char cliffData[] = {6,0,0}; //<LightSensor()6, which sensor(0,1,2,3), cliff(0)/boundary(1)>
            transmit_str_num(cliffData, 3); //TODO:
            lCliffSent = true;
            return;
        }
    }else{
        lCliffSent = false;
    }
    if(sensor_data->cliffFrontLeftSignal <= CLIFF_EDGE){
        move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!flCliffSent){
            char cliffData[] = {6,1,0};
            transmit_str_num(cliffData, 3); //TODO:
            flCliffSent = true;
            return;
        }
    }else{
        flCliffSent = false;
    }
    if(sensor_data->cliffFrontRightSignal <=  CLIFF_EDGE){
        move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!lCliffSent){
            char cliffData[] = {6,2,0};
            transmit_str_num(cliffData, 3); //TODO:
            frCliffSent = true;
            return;
        }
    }else{
        frCliffSent = false;
    }
    if(sensor_data->cliffRightSignal <=  CLIFF_EDGE){
        move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!lCliffSent){
            char cliffData[] = {6,3,0};
            transmit_str_num(cliffData, 3); //TODO:
            rCliffSent = true;
            return;
        }
    }else{
        rCliffSent = false;
    }


    //check_if_target();

}
//bumpers_f MAKE like CLIFF
void check_bumpers_f()
{
    static bool lBumpSent = false;
    static bool rBumpSent = false;

    if(sensor_data->bumpLeft){
        if(!lBumpSent){
            char bumpData[] = {1,2};
            transmit_str_num(bumpData,2);
            move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
            lBumpSent = true;
            return;
        }
    }else{
        lBumpSent = false;
    }

    if(sensor_data->bumpRight){
        if(!rBumpSent){
            char bumpData[] = {1,3};
            transmit_str_num(bumpData,2);
            move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
            rBumpSent = true;
            return;
        }
    }else{
        rBumpSent = false;
    }

}


//boundary

void check_boundary_f()
{


    static bool lBoundarySent = false;
    static bool flBoundarySent = false;
    static bool frBoundarySent = false;
    static bool rBoundarySent = false;

    if(sensor_data->cliffLeftSignal >= BOUNDARY){
        move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!lBoundarySent){
            char boundaryData[] = {6,0,1}; //<LightSensor()6, which sensor(0,1,2,3), cliff(0)/boundary(1)>
            transmit_str_num(boundaryData, 3); //TODO:
            lBoundarySent = true;
            return;
        }
    }else{
        lBoundarySent = false;
    }
    if(sensor_data->cliffFrontLeftSignal >= BOUNDARY){
        move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!flBoundarySent){
            char boundaryData[] = {6,1,1};
            transmit_str_num(boundaryData, 3); //TODO:
            flBoundarySent = true;
            return;
        }
    }else{
        flBoundarySent = false;
    }
    if(sensor_data->cliffFrontRightSignal >=  BOUNDARY){
        move_back_mm_at_speed(30 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!frBoundarySent){
            char boundaryData[] = {6,2,1};
            transmit_str_num(boundaryData, 3); //TODO:
            frBoundarySent = true;
            return;
        }
    }else{
        frBoundarySent = false;
    }
    if(sensor_data->cliffRightSignal >=  BOUNDARY){
        move_back_mm_at_speed(10 /*cm*/, DRIVE_SPEED, sensor_data);
        if(!rBoundarySent){
            char boundaryData[] = {6,3,1};
            transmit_str_num(boundaryData, 3); //TODO:
            rBoundarySent = true;
            return;
        }
    }else{
        rBoundarySent = false;
    }

}

flags* getFlags(){
    return flag_data;
}
