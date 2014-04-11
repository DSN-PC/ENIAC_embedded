/*********************************************************************
 *
 *                          WSN Board Main
 *
 *********************************************************************
 * FileName:        	Main.c
 * Dependencies:	None
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.34 or higher
 *
 * Company:
 *
 * Author		Date            Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vas �d�m             02/09/13        Created
 *********************************************************************/

/*
 * This macro uniquely defines this file as the main entry point
 * There should only be one such definition in the entire project
 * and this file must define the AppConfig variable as described below.
 */
#define THIS_IS_STACK_APPLICATION

#define TIMER2_TICKS_PER_SECOND     (1.0 / ((1.0/GetInstructionClock())*(PR2+1.0)*16.0*8.0) ) // 1:16 prescaler, 1:8 postscaler
#define TIMER2_TICKS_PER_MINUTE     (60.0*TIMER2_TICKS_PER_SECOND)



/* Include all headers for any enabled TCPIP Stack functions */
#include "TCPIP Stack\TCPIP.h"

/* Include functions specific to this stack application */
#include "Main.h"

/***************************************************************************************************
                                       Function prototypes
 ***************************************************************************************************/
void InitializeBoard(void);
void InitAppConfig(void);
void SevenSegmentDisplay(int value);
void SevenSegmentISR(void);
BOOL EniacNode(void);


/***************************************************************************************************
                                        Global variables
 ***************************************************************************************************/
extern APP_CONFIG AppConfig;


/***************************************************************************************************
                                    Interrupt Service Routines
 ***************************************************************************************************/
#pragma interruptlow LowISR
void LowISR(void)
{
    if (INTCONbits.TMR0IF)
    {
        TickUpdate();        
    }

    if (PIR1bits.TMR2IF)
    {
        /* Switch 7-segment display to the next digit */
        SevenSegmentISR();

        /* Clear Interrupt flag */
        PIR1bits.TMR2IF = 0;
    }
}

#pragma interrupt HighISR
void HighISR(void)
{
    
}

#pragma code lowVector=0x18
void LowVector(void){_asm goto LowISR _endasm}
#pragma code highVector=0x8
void HighVector(void){_asm goto HighISR _endasm}

/* Return to default code section */
#pragma code 
/************************************************************************************************
				Main application entry point.
************************************************************************************************/
void main(void)
{
    /* Initialize hardware components. */
    InitializeBoard();

    /* Initialize the Tick manager module. */
    TickInit();

    /* Initialize Stack and application related variables into AppConfig. */
    InitAppConfig();

    /* Initialize core stack layers (MAC, ARP, TCP, UDP) and
       application modules (HTTP, SNMP, etc.) */
    StackInit();
    
    while(1)
    {        
        /* This task performs normal stack task including checking
           for incoming packet, type of packet and calling
           appropriate stack entity to process it. */
        StackTask();

        /* This tasks invokes each of the core stack application tasks. */
        StackApplications();

        /* ENIAC calculation tasks. */
        EniacNode();
    }
}
