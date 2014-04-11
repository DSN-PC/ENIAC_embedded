/*********************************************************************
 *
 *                  Hardware specific definitions
 *
 *********************************************************************
 * FileName:        	HWP DSNPC_BOARD.h
 * Dependencies:	None
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.34 or higher
 *
 * Company:
 *
 * Author		Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ing Manuel Malagon	1/03/11		Modification from Original
 * Vas Adam             02/09/13        Modified for DSNPC_BOARD
 *********************************************************************/
#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

/* Board ID */
#define DSNPC_BOARD_ID          (*(far rom WORD*)0x1FFF6)

/* Clock frequency value */
#define GetSystemClock()	(41666667ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define GetPeripheralClock()	GetInstructionClock()

/******************************************************************************************
				I/O Pins

	Here you specify all the IO pins you are going to use, this definitions are
	according to your particular board.
*******************************************************************************************/

/* Push button */
#define BUTTON_TRIS         (TRISEbits.TRISE1)
#define BUTTON              (PORTEbits.RE1)

/* 7-segment display pins */
#define DISP_SEG_TRIS       (TRISF)
#define DISP_DG_TRIS        (TRISB)
#define DISP_SEG            (PORTF)
#define DISP_DG             (PORTB)

#endif
