
#include <stdbool.h>
#include "lcd.h"
#include "uart.h"
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
    int size = 2 * pingMid*(tan((theta/2)*(PI/180)));

    if(size < minVal){
        minVal = size;
        minDegrees = midNum;
    }


    transmit_str(message);
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
                    newObjectEnd = clockwise ? convertedDegrees+2 : convertedDegrees-2;
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

}
