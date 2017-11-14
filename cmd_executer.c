//Command Executer
//CPRE_288
//author: Christopher Caldwell

#include <stdio.h>
#include "cmd_executer.h"

void cmd_ex()
{
  //printf("cmd_array[0]\n");
  int num_data_b = rtn_cmd_len(cmd_array_in[0]);
  int i = 0;
  char command[5] = {0};
  printf("num_data_b is %d\n", num_data_b);
  command[0] = cmd_array_in[0];
  for(i=1;i<=num_data_b;i++)
  {
    command[i] = cmd_array_in[i];
  }
  //function to call functions:
  //call_functions(command)
}

int rtn_cmd_len(char cmd_byte)
{

  int cmd_len = 0;

  switch(cmd_byte) {
     case '0' : //forward/reverse; <cmd>, <left_wheel>, <right_wheel>
        cmd_len = 2;
        break;
     case '1' : //left/right; <cmd>, <left_wheel>, <right_wheel>
        cmd_len = 2;
        break;
     case '2' : //scan for objects
        cmd_len = 0;
        break;
  }

  return cmd_len;
}

//call function
void call_functions(char *command_info_array)
{
  //case '2' : //scan for objects
  //   cmd_len = 0;
  //   break;
}
