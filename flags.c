//flags module
#include "flags.h"
#include <stdbool.h>


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


/*TODO:
WRITE LOGIC TO DIFFERENTIATE BETWEEN THINGS.


cliff: ((sensor_data->wheelDropLeft)|(sensor_data->wheelDropLeft));
IDENTIFY THE cliff
*/

void check_flags()
{
  oi_update(sensor_data);

  set_drop_f();
  check_cliff_sensors();
  check_bumpers_f();
  check_boundary_f();


  //            if(flag_data->cliff_f)
  //            {
  //              move_back_mm_at_speed(10, -DRIVE_SPEED, sensor_data);
  //              oi_setWheels(0,0); //stop wheels
  //              //TODO: transmit cliff data
  //
  //            }
  //
  //            else if(flag_data->bumpers_f)
  //            {
  //              //move_back_mm_at_speed(20, -DRIVE_SPEED, sensor_data);
  ////              int cm = 20;
  ////              int i = 0;
  ////              move_straight(-DRIVE_SPEED, sensor_data);
  ////              while (i < cm)
  ////              {
  ////                  oi_update(sensor_data);
  ////                  i -= sensor_data->distance;
  ////              }
  ////              oi_setWheels(0,0); //stop wheels
  //
  //              //TODO:transmit small object data
  //
  //            }
  //            else if(flag_data->boundary_f)
  //            {
  //
  //              //TODO:transmit where boundary is
  //            }
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
  if((sensor_data->cliffLeft) || (sensor_data->cliffFrontLeft) || (sensor_data->cliffFrontRight) || (sensor_data->cliffRight))
  {

    if(sensor_data->cliffLeft < TARGET_MIN) //TODO CHANGE TARGET_MIN AND MAX
    {
      cliff_f |= cliffL_s;
    }

    if(sensor_data->cliffFrontLeft < TARGET_MIN)
    {
      cliff_f |= cliffFL_s;
    }

    if(sensor_data->cliffFrontRight < TARGET_MIN)
    {
      cliff_f |= cliffFR_s;
    }

    if(sensor_data->cliffRight)
    {
      cliff_f |= cliffR_s;
    }
  }
}

    //check_if_target();


//bumpers_f MAKE like CLIFF
void check_bumpers_f()
{
  if((sensor_data->bumpLeft) || (sensor_data->bumpRight))
  {
    if(sensor_data->bumpLeft)
    {
        bumpers_f |= bumpL_f;
    }
    if(sensor_data->bumpRight)
    {
        bumpers_f |= bumpR_f;
    }
    if((sensor_data->bumpRight) && (sensor_data->bumpLeft))
    {
        bumpers_f |= bumpF_f;
    }

  }
}

//boundary

void check_boundary_f()
{

    {
      boundary_f |= cliffL_s;
    }
    if(sensor_data->cliffFrontLeftSignal >= BOUNDARY)
    {
      cliff_f |= cliffFL_s;
    }
    if(sensor_data->cliffFrontRightSignal >= BOUNDARY)
    {
      cliff_f |= cliffFR_s;
    }
    if(sensor_data->cliffRightSignal >= BOUNDARY)
    {
      cliff_f |= cliffR_s;
    }
}

flags* getFlags(){
    return flag_data;
}
