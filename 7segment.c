/*********************************************************************
 *
 *			7-segment display functions
 *
 *********************************************************************
 * FileName:        	7segment.c
 * Dependencies:	HDSP-B03E 7-segment display
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.34 or higher
 *
 * Company:
 *
 * Author				Date			Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vas Ádám                             25/06/12		Created
 *
 *********************************************************************/
/* Include functions specific to this stack application */
#include "Delay.h"
#include "HardwareProfile.h"


/* Function Prototypes */
void SevenSegmentDisplay(UINT16 value);
static void SevenSegment(UINT8 value);
void SevenSegmentISR(void);


/* Array containing digits to display */
static UINT8 digits[4];


/****************************************************************************
  Function:
    static void SevenSegment(UINT8 value)

  Description:
    This routine is used to display one digit on the 7-segment display.
    Do not call this directly, it is called by SevenSegmentISR().

  Precondition:
    None

  Parameters:
    value - the one-digit value to display

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
static void SevenSegment(UINT8 value)
{
    switch (value)
    {
        case 0: DISP_SEG = 0b01111110; break;
        case 1: DISP_SEG = 0b00001100; break;
        case 2: DISP_SEG = 0b10110110; break;
        case 3: DISP_SEG = 0b10011110; break;
        case 4: DISP_SEG = 0b11001100; break;
        case 5: DISP_SEG = 0b11011010; break;
        case 6: DISP_SEG = 0b11111010; break;
        case 7: DISP_SEG = 0b00001110; break;
        case 8: DISP_SEG = 0b11111110; break;
        case 9: DISP_SEG = 0b11011110; break;
        default: DISP_SEG = 0b00000000;
    }
}


/****************************************************************************
  Function:
    void SevenSegmentDisplay(UINT16 value)

  Description:
    This routine is used to write values on the 7-segment display.
    It takes a 16 bit unsigned integer argument and splits it into
    individual digits and updates the digits[] array.

  Precondition:
    None

  Parameters:
    value - the value to display (0-9999)

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void SevenSegmentDisplay(UINT16 value)
{
    int i=0, j;

    if (value>9999u)
        for (i=0; i<4; i++)
            digits[i] = 9;
    else
    {
        do
        {
            digits[i++] = value%10;
            value = value/10;
        } while(value);

        for (j=i; j<4; j++)
            digits[j] = -1;
    }
}


/****************************************************************************
  Function:
    void SevenSegmentISR(void)

  Description:
    This routine is called by the ISR to shift the 7-segment display to the
    next digit and pass the actual value of that digit to the SevenSegment()
    function.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void SevenSegmentISR(void)
{
   static INT8 i;

   if (i==3)
      i=0;      // If currently the last digit is active then switch back to the first one
   else
      i++;      // Switch to the next digit

   /* Activate a digit according to i */
   DISP_DG = ((DISP_DG & 0xf0) | (0x08 >> i));

   /* Display digit[i] */
   SevenSegment(digits[i]);
}
