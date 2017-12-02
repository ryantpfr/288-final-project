//flags module

char cliff_f = 0; //boolean

#define cliffL_f 0b1000;
#define cliffFL_f 0b0100;
#define cliffFR_f 0b0010;
#define cliffR_f 0b0001;

char target_f = 0;

char bumpers_f = 0;

//make these defines.
bool bumpR_f = 0;
bool bumpL_f = 0;
bool bumpF_f = 0;

char boundary_f = 0;
bool drop_f = 0;

TODO:
WRITE LOGIC TO DIFFERENTIATE BETWEEN THINGS.

/*
cliff: ((sensor_data->wheelDropLeft)|(sensor_data->wheelDropLeft));
IDENTIFY THE cliff
*/

void check_flags()
{
  set_drop_f();
  check_cliff_sensors();
  check_bumpers_f();
  check_boundary_f();
}

bool set_drop_f()
{
  if((sensor_data->wheelDropLeft)|(sensor_data->wheelDropLeft))
  {
    drop_f = 1;
  }
  return drop_f;
}

void check_cliff_sensors() //?? Not sure if this is correct ?? FIXME
{
  if((sensor_data->cliffLeft)|(sensor_data->cliffFrontLeft)|(sensor_data->cliffFrontRight)|(sensor_data->cliffRight))
  {
    if((sensor_data->cliffLeftSignal >= target_min) &&(sensor_data->cliffLeftSignal <= target_max))
    {
      target_f |= cliffL_s;
    }
    if(sensor_data->cliffLeft < target_min)
    {
      cliff_f |= cliffL_s;
    }

    if((sensor_data->cliffFrontLeftSignal >= target_min) &&(sensor_data->cliffFrontLeftSignal <= target_max))
    {
      target_f |= cliffFL_s;
    }
    if(sensor_data->cliffFrontLeft < target_min)
    {
      cliff_f |= cliffFL_s;
    }

    if((sensor_data->cliffFrontRightSignal >= target_min) &&(sensor_data->cliffFrontRightSignal <= target_max))
    {
      target_f |= cliffFR_s;
    }
    if(sensor_data->cliffFrontRight < target_min)
    {
      cliff_f |= cliffFR_s;
    }

    if((sensor_data->cliffRightSignal >= target_min) &&(sensor_data->cliffRightSignal <= target_max))
    {
      target_f |= cliffR_s;
    }
    if(sensor_data->cliffRight)
    {
      cliff_f |= cliffR_s;
    }

    //check_if_target();

}

//bumpers_f MAKE like CLIFF
void check_bumpers_f()
{
  if((sensor_data->bumpLeft)|(sensor_data->bumpRight))
  {
    bumpers_f = 1;
    if((sensor_data->bumpLeft)
    {
      bumpL_f = 1;
    }
    if(sensor_data->bumpRight)
    {
      bumpR_f = 1;
    }
    if((sensor_data->bumpRight)&(sensor_data->bumpLeft))
    {
      bumpF_f = 1;
    }

}

//boundary

void check_boundary_f()
{
    if((sensor_data->cliffLeftSignal >= BOUNDARY)
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
