#include "stdbool.h"

struct CollisionResult{
    bool collision;
    bool right;
    int mm;
};

void move_mm_at_full_speed(int cm, oi_t* sensor_data);

void move_mm_at_speed(int cm, int speed, oi_t* sensor_data);

struct CollisionResult move_mm_at_speed_until_collision(int cm, int speed, oi_t* sensor_data);

void move_back_mm_at_speed(int cm, int speed, oi_t* sensor_data);

void turn_right(int degrees,oi_t* sensor_data);

void turn_left(int degrees, oi_t* sensor_data);
