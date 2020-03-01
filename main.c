#include <xc.h>
#include "config.h"
#include "Macros.h"
#include "Std_Types.h"
#include "INTERRUPTS_interface.h"
#include "LCD_interface.h"
#include "DIO_interface.h"
#include "I2C_interface.h"
#include "ADC_private.h"
#include "KEYPAD_interface.h"
#include "APP_interface.h"
#include "SERVICES_interface.h"
#include "TIMER0_interface.h"
#include "COMMON_private.h"
#define _XTAL_FREQ 4000000


extern u8 u8RestartSys;

void main(void)
{
    APP_vidInit();
    DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN0,DIO_INPUT);
    
    /*Configuring external interrupt used to restart system*/
    INTERRUPTS_vidEnableInterrupt(INTERRUPTS_EXT);
    INTERRUPTS_vidSetExtInterruptEdge(INTERRUPTS_EDGE_FALLING);
    INTERRUPTS_vidPutISR(INTERRUPTS_EXT,APP_vidRestartSystem);
    INTERRUPTS_vidEnablePeripheralInterrupt();

    /*Timer0 configuration*/
    TIMER0_vidInit(TIMER0_MODE_TIMER,TIMER0_PS_2);   
    
    DIO_vidControlPullUp(DIO_PULLUP);
    KEYPAD_vidInit();
  
    LCD_vidInit();
    DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_OUTPUT);
    INTERRUPTS_vidPutISR(INTERRUPTS_TIMER0_OVF,vidCountOVF);
    INTERRUPTS_vidEnableGlobalInterrupt();

    APP_vidRestartSystem();
    
  
    
    while (1)
    {
                SERVICES_u8WriteCharacter();

    }
}