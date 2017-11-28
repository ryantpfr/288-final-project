
#include "uart.h"
#include "lcd.h"
#include "cmd_executer.h"

int commandRemaining = -1;
char command[5];
int commandPosition = 0;

int execute_command(){
    switch(command[0]){
        case(2) :
            exe_scan();
            break;
    }

}

int rtn_cmd_len(char cmd_byte)
{

  int cmd_len = 0;

  switch(cmd_byte) {
     case 0 : //forward/reverse; <cmd>, <left_wheel>, <right_wheel>
        cmd_len = 2;
        break;
     case 1 : //left/right; <cmd>, <left_wheel>, <right_wheel>
        cmd_len = 2;
        break;
     case 2 : //scan for objects
        cmd_len = 0;
        break;
  }

  return cmd_len;
}

void take_char(char c_in)
{

    command[commandPosition] = c_in;
    if(commandRemaining == -1)
    {
        commandRemaining = rtn_cmd_len(c_in) + 1;
    }
    commandRemaining--;
    if(commandRemaining == 0)
    {
        execute_command();
        commandRemaining = -1;
        commandPosition = 0;
    }
}
