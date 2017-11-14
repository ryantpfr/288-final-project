
#include "uart.h"
#include "lcd.h"

volatile int *commandRemaining;
volatile char *command;

int commandSizeDict(char c){
    switch(c){
        case(1) : return 1;
    }

    return -1; //review error handling
}

int execute_command(){
    return 1;
}

void command_parser_init(char* cmd,int *cmdRemaining){
    command = cmd;
    commandRemaining = *cmdRemaining;
}
