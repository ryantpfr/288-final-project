#include "open_interface.h"
#include "lcd.h"
#include "stdio.h"
#include "movement.h"
#include "exe_op.h"



void move_cm_at_full_speed(int cm, oi_t* sensor_data){
    move_mm_at_speed(cm, 500, sensor_data);
}

void move_stop(oi_t* sensor_data){
    oi_setWheels(0, 0);
}

void move_straight(int speed, oi_t* sensor_data){

    if (speed > 0)
    {
      oi_setWheels(speed, speed);
      lcd_printf("forward");
    }
    else if (speed == 0)
    {
      oi_setWheels(speed, speed);
      lcd_printf("stop");
    }
    else if (speed < 0)
    {
      oi_setWheels(-speed, -speed);
      lcd_printf("reverse");
    }
}

void move_mm_at_speed(int cm, int speed, oi_t* sensor_data){

 //   lcd_printf("hello world2");

    int sum = 0;
       oi_setWheels(speed, speed); // move forward; full speed
       while (sum < cm) {
           oi_update(sensor_data);
           sum += sensor_data->distance;
       }
       oi_setWheels(0, 0); // stop
}


void move_back_mm_at_speed(int cm, int speed, oi_t* sensor_data){

   // lcd_printf("hello world2");

    int sum = 0;
       oi_setWheels(-speed, -speed); // move forward; full speed
       while (sum < cm) {
           oi_update(sensor_data);
           sum -= sensor_data->distance;
       }
       oi_setWheels(0, 0); // stop
}

struct CollisionResult move_mm_at_speed_until_collision(int cm, int speed, oi_t* sensor_data){

    lcd_printf("%d\n", sensor_data->bumpLeft);

    int sum = 0;
    bool leftBumper = sensor_data->bumpLeft == 1;
    bool rightBumper = sensor_data->bumpRight == 1;
    oi_setWheels(speed, speed); // move forward; full speed

    while (sum < cm && !leftBumper && !rightBumper) {
       oi_update(sensor_data);
       sum += sensor_data->distance;
       lcd_printf("%d\n", sensor_data->bumpLeft);

       leftBumper = sensor_data->bumpLeft == 1;
       rightBumper = sensor_data->bumpRight == 1;

       lcd_printf("%d\n%d\n%d",leftBumper,rightBumper,cm - sum);
    }
    oi_setWheels(0, 0); // stop

    struct CollisionResult res;
    res.collision = sum < cm;
    res.right = rightBumper;
    res.mm = sum;

    return res;
}

void turn_right(int degrees, oi_t* sensor_data)
{
    degrees = (int) degrees * TURN_CALIBRATION;

    //int stopAt = sensor_data->angle - degrees;
    int sum = 0;
     oi_setWheels(-TURN_SPEED, TURN_SPEED); // move forward; full speed
     while (sum < degrees) {
      oi_update(sensor_data);
       sum += abs(sensor_data->angle);
       lcd_printf("%d\n%d\n",sensor_data->angle, sum);
     }
     oi_setWheels(0, 0);
}

void turn_left(int degrees, oi_t* sensor_data)
{
    int stopAt = sensor_data->angle + degrees;
    int sum = 0;
     oi_setWheels(TURN_SPEED,-TURN_SPEED); // move forward; full speed
     while (sum < stopAt) {
      oi_update(sensor_data);
       sum += sensor_data->angle;
       lcd_printf("%d\n%d\n",sensor_data->angle, sum);
     }
     oi_setWheels(0, 0);
}

void turn(char dir, oi_t* sensor_data)
{
    if(dir > -1) //right
    {
        oi_setWheels(-TURN_SPEED, TURN_SPEED);
    }
    else if(dir == 0) //stop; might not be necessary
    {
        oi_setWheels(0, 0);
    }
    else if(dir == 1) //left
    {
        oi_setWheels(TURN_SPEED, -TURN_SPEED);
    }

    return sensor_data->angle;
}


