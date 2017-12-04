
#include "timer.h"
#include "lcd.h"
#include "button.h"
#include <stdbool.h>

void transmit_str(char str[]);
void transmit_str_num(char str[],int num);
void uart_init(void);
void uart_transmit(char c);
void translate_and_transmit(char c);
void uart_receive(void);
void UART1_Handler(void);
char uart_receive2(void);
char readLChar();
bool readLCharRead();
void setLCharRead();
char uart_receive_last(void);
