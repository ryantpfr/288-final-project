
#include "uart.h"
#include "lcd.h"
#include "cmd_executer.h"

int commandRemaining = -1;
char command[5];
int commandPosition = 0;

// int execute_command(){
//     switch(command[0]){
//     case(0) :
//         (command[1], command[2]);
//         break;
//     case(1) :
//         exe_turn(command[1], command[2]);
//         break;
//     case(2) :
//         exe_scan();
//         break;
//     case(3) :
//         exe_scan();
//         break;
//     }
//
// }

// int rtn_cmd_len(char cmd_byte)
// {
//
//   int cmd_len = 0;
//
//   switch(cmd_byte) {
//
//      case 0 : //forward/reverse : <cmd> <speed> : ex. cmds: 0 100 or 0 -100
//         cmd_len = 2;
//         break;
//      case 1 : //turn distance t; <cmd>, <dir>, <degrees/2> //turns from -90 -> 90
//         cmd_len = 2;
//         break;
//      case 2 : //scan for objects
//         cmd_len = 0;
//         break;
//      case 3 : //play song <song, num>
//         cmd_len = 0;
//         break;
//
// //   }
//
//   return cmd_len;
// }

void take_char(char c_in)
{

    command[commandPosition] = c_in;
    commandPosition++;
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
