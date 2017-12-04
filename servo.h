
void gpio_pb5_init();
void timer1_init();
void servo_set_degrees(float degrees);
void calibration_test();
void servo_set_degrees_bounded(float degrees);
void servo_set_degrees_scan(float degrees);



#define CLOCK_LOAD 320000L
#define CLOCK_MID 298324
#define DEGREE_SCALE 156
