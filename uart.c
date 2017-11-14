
#include "uart.h"

volatile char lastCharacter;
volatile bool lastCharacterRead = true;

//volatile char command[20];
//volatile int commandLength;
//volatile int commandRemaining = -1;

void transmit_str(char str[]){
    int i;
    for(i = 0; str[i] != '\0'; i++){
        uart_transmit(str[i]);
    }
    uart_transmit('\r');
    uart_transmit('\n');
}

char readLChar(){
    return lastCharacter;
}


bool readLCharRead(){
    return lastCharacterRead;
}

void setLCharRead(){
    lastCharacterRead = true;
}

void uart_init(void)
{
 //enable clock to GPIO, R1 = port B
 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
 //enable clock to UART1, R1 = UART1. ***Must be done before setting Rx and Tx (See DataSheet)
 SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
 //enable alternate functions on port b pins 0 and 1
 GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);
 //enable Rx and Tx on port B on pins 0 and 1
 GPIO_PORTB_PCTL_R |= 0x00000011;
 //set pin 0 and 1 to digital
 GPIO_PORTB_DEN_R |= (BIT0 | BIT1);
 //set pin 0 to Rx or input
 GPIO_PORTB_DIR_R &= ~BIT0;
 //set pin 1 to Tx or output
 GPIO_PORTB_DIR_R |= BIT1;
 //calculate baudrate
 uint16_t iBRD =8; //use equations

 uint16_t fBRD =44; //use equations
 //turn off uart1 while we set it up
 UART1_CTL_R &= ~(UART_CTL_UARTEN);
 //set baud rate
 UART1_IBRD_R = iBRD;
 UART1_FBRD_R = fBRD;
 //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
 UART1_LCRH_R = UART_LCRH_WLEN_8 ;
 //use system clock as source
 UART1_CC_R = UART_CC_CS_SYSCLK;
 //re-enable enable RX, TX, and uart1
 UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

 ///////////////////////////////////Interrupts///////////////////////////////////////////

 //turn off uart1 while we set it up
  UART1_CTL_R &= ~(UART_CTL_UARTEN);
  //clear interrupt flags
  UART1_ICR_R = (UART_ICR_TXIC | UART_ICR_RXIC);
  //enable send and receive raw interrupts
  UART1_IM_R |= UART_IM_TXIM | UART_IM_RXIM;
  //set priority of usart1 interrupt to 1. group 1 bits 21-23
  NVIC_PRI1_R |= 0x00200000;
  //enable interrupt for IRQ 6 set bit 6
  NVIC_EN0_R |= 0x00000040;
  //tell cpu to use ISR handler for uart1
  IntRegister(INT_UART1, UART1_Handler);
  //enable global interrupts
  IntMasterEnable();

  //re-enable enable RX, TX, and uart1
  UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

}//END of uart_init()

void uart_transmit(char c){

    while(UART1_FR_R & 0x20);

    UART1_DR_R = c;

}

void translate_and_transmit(char c){
    uart_transmit(c);


    if(c == '\r'){
        uart_transmit('\n');
        return;
    }
}

//Blocking call to receive over uart1
//returns char with data
void uart_receive(void)
{

    char data;

    //mask the 4 error bits and grab only 8 data bits
    data = (char)(UART1_DR_R & 0xFF);

    //removed for final project
    //if( data=='\r' || data=='\n') return;

    lastCharacter = data;
    lastCharacterRead = false;
}

//Interrupt handler for uart1
void UART1_Handler(void){
    //received a byte
    if(UART1_MIS_R & UART_MIS_RXMIS){
        uart_receive();
        UART1_ICR_R |= UART_ICR_RXIC; //clear interrupt
    }
    //sent a byte
    else if(UART1_MIS_R & UART_MIS_TXMIS){
        //Do something
        UART1_ICR_R |= UART_ICR_TXIC; //clear interrupt
    }
}

char uart_receive2(void)
{

    char data;

    while(lastCharacterRead){

    }
    //mask the 4 error bits and grab only 8 data bits
    data = lastCharacter;

    lastCharacterRead = true;

    return data;
}


