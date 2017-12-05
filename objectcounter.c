
#include "timer.h"
#include <stdbool.h>
#include "lcd.h"
#include "button.h"
#include "servo.h"
#include "uart.h"
#include "wifi.h"
#include "banner.h"
#include "ir.h"
#include "ping2.h"
#include <math.h>

#define SENSITIVITY 800
#define PI 3.14159f


typedef struct{
    int ping;
    int ir;
} MeasurementData;

typedef struct{
    int objectStart;
    int objectEnd;
    int size;
} Object;

typedef enum{
    no_obj,
    testing_front_edge,
    curr_obj,
    testing_back_edge
} ObjectState;


MeasurementData data[181];
int objCount = 0;
Object objects[10];
ObjectState state;
bool clockwise = false;
int lastIr = 0;
int newObjectStart;
int newObjectEnd;
int minDegrees = 0;
int minVal = 9999;

void createObject(){
    objCount++;

    int midNum = (newObjectStart+newObjectEnd)/2;
    midNum = midNum % 2 == 1 ? midNum-1 : midNum;

    int pingMid = data[midNum].ping;
    int theta = newObjectEnd - newObjectStart;

    char message[100];
    sprintf(message,"\r\nObject Created\r\nfrom degrees %d to %d\r\nping mid distance is %d",newObjectStart-90,newObjectEnd-90,pingMid);


//    int size = (tan((theta/2)*(PI/180))*pingMid)/(1-tan((theta/2)*(PI/180)))*1.5;
    uint32_t size = 2 * pingMid*(tan((theta/2)*(PI/180)));

    if(size < minVal){
        minVal = size;
        minDegrees = midNum;
    }

    char objData[] = {5,newObjectStart,newObjectEnd,pingMid >> 8,pingMid};

    transmit_str_num(objData,5);

    //lcd_printf(objData);

    //while(true);

    //transmit_str(message);
}

void counter_write(int degrees, int ir, int ping){
    int convertedDegrees = degrees+90;
    data[convertedDegrees].ir = ir;
    data[convertedDegrees].ping = ping;

    switch(state){
        case(no_obj) :
                if(ir < SENSITIVITY){
                    state = testing_front_edge;
                    newObjectStart = convertedDegrees;
                }
                break;
        case(testing_front_edge) :
                if(ir < SENSITIVITY){
                    state = curr_obj;
                }else{
                    state = no_obj;
                }
                break;
        case(curr_obj) :
                if(ir > SENSITIVITY)
                {
                    state = testing_back_edge;
                }
                break;
        case(testing_back_edge) :
                if(ir > SENSITIVITY){
                    state = no_obj;
                    newObjectEnd = clockwise ? convertedDegrees+2: convertedDegrees-2;
                    createObject();
                }else{
                    state = curr_obj;
                }
                break;
    }


    lastIr = ir;
}

int getObjCount(){
    return objCount;
}

int getMinDegrees(){
    return minDegrees - 90;
}

int getMinSize(){
    return minVal;
}

void objCounterReset(){
    objCount = 0;
    lastIr = 0;
    minDegrees = 0;
    minVal = 9999;
}


void reset_direction(int* direction, int* degrees){
    if(*degrees >= 90){
        *direction = -1;
    }else if(*degrees <= -90){
        *direction = 1;
    }

}

void sweep_and_send(){

    char startCommand[] = {4};
    transmit_str_num(startCommand,1);
    objCounterReset();

    int direction = 1;

    int degrees = -90;

    while(degrees != 90 || false){

       gpio_ping_micros(10);

       degrees += direction*2;
       servo_set_degrees_scan(degrees);
       reset_direction(&direction,&degrees);

       int irData = IR_ReadMM();
       uint32_t pingData = read_ping_when_done();

       counter_write(degrees,irData,pingData);

       char message[20];
       sprintf(message,"%d : %d : %d\n%d",degrees, irData , pingData,getObjCount());

       lcd_printf(message);

    }

    servo_set_degrees(-90);

}
