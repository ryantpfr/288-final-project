
#include "timer.h"
#include "lcd.h"
//#include "button.h"
#include <stdbool.h>


//
//void ADC0SS0_Handler(void)
//{
//    //initiate SS1 conversion
//    ADC0_PSSI_R=ADC_PSSI_SS0;
//
//    //wait for ADC conversion to be complete
//    while((ADC0_RIS_R & ADC_RIS_INR1) == 0)
//    {
//    //wait
//    }
//    //grab result
//    int value = ADC0_SSFIFO0_R;
//    lcd_printf("%d",value);
//
//}


void IR_init(void)
{

    //enable ADC 0 module on port D
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;

    //enable clock for ADC
    SYSCTL_RCGCADC_R |= 0x1;

    //enable port D pin 0 to work as alternate functions
    GPIO_PORTD_AFSEL_R |= 0x01;

    //set pin to input - 0
    GPIO_PORTD_DEN_R &= 0b11111110;

    //disable analog isolation for the pin
    GPIO_PORTD_AMSEL_R |= 0x01;

    //initialize the port trigger source as processor (default)
    GPIO_PORTD_ADCCTL_R = 0x00;

    //disable SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;

    //set 1st sample to use the AIN10 ADC pin
    ADC0_SSMUX0_R |= 0x000A;

    //enable raw interrupt status
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);

    //enable oversampling to average
    ADC0_SAC_R |= ADC_SAC_AVG_64X; //auto averages

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

    //by Ryan, you can delete
//    ADC0_VDDA_R=0;
//    ADC0_GNDA_R =3;

    /////////////////////////Enable ADC interrupt handler////////////////////////////
   /* //clear interrupt flags
    ADC0_ISC_R |= ADC_ISC_IN0;

    //enable ADC0SS0 interrupt
    ADC0_IM_R |= ADC_IM_MASK0;

    //enable interrupt for IRQ 14 set bit 14
    NVIC_EN0_R |= 0x00004000;

    //tell cpu to use ISR handler for ADC0SS0
    IntRegister(INT_ADC0SS0, ADC0SS0_Handler);

    //enable global interrupts
    IntMasterEnable();*/
}//END of IR_init()



int IR_ReadMM(){
    ADC0_PSSI_R=ADC_PSSI_SS0;
    //wait for ADC conversion to be complete

    while((ADC0_RIS_R & ADC_RIS_INR0) == 0)
    {
    //wait
    }
    //grab result
    int value = ADC0_SSFIFO0_R;

    //int disatnce =(357759/(value)-60);
    //int disatnce = ((323164/(value)-60)+15)*1.033;
    return  ((((((323164/(value)-60)+15)*1.033)+36)*0.909+12)*1.16)*0.974-18;
}



//int main(void)
//{
//    lcd_init();
//
//    IR_init();
//
//    lcd_printf("Hello");
//    while(1)
//    {
//
//        timer_waitMillis(500);
//
//    int disatnce = IR_ReadMM();
//
//    lcd_printf("%d",disatnce);
//
//    }
//    return 0;
//}
