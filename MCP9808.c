/*********************************************************************
 *
 *       Microchip MCP9808 digital temperature sensor functions
 *
 *********************************************************************
 * FileName:        	MCP9808.c
 * Dependencies:	Microchip MCP9808 digital temperature sensor
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.34 or higher
 *
 * Company:
 *
 * Author				Date			Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vas �d�m                             09/07/12		Created
 *********************************************************************/

#include "GenericTypeDefs.h"

/* MPC9808 register addresses */
#define MCP_ADDRESS         0x30        // 0x30 Address
#define MCP_TA_MSB          0x05        // 0x05 TA Register MSB

/* Function Prototypes */
void I2CRegReadN(BYTE address, BYTE reg1, BYTE n, BYTE *array);

/****************************************************************************
  Function:
    float ReadTemperatureMCP9808(void)

  Description:
    This routine is used to read the temperature value
    from the Microchip MCP9808 digital I2C barometer.

  Precondition:
    I2C is initialized.

  Parameters:
    None

  Returns:
    Temperature (°C)

  Remarks:
    None
  ***************************************************************************/
float ReadTemperatureMCP9808(void) {
    BYTE T_bytes[2];        // Temperature MSB, LSB
    BOOL is_negative;
    float T;                // Temperature value in �C

    I2CRegReadN(MCP_ADDRESS, MCP_TA_MSB, 2, T_bytes);

    if (T_bytes[0] & 0x10)  // TA < 0�C
    {
        is_negative = TRUE;
        T = 256 - ((T_bytes[0] << 4) + (T_bytes[1] >> 4));
    }
    else                    // TA >= 0�C
    {
        is_negative = FALSE;
        T = (T_bytes[0] << 4) + (T_bytes[1] >> 4);
    }

    if (T_bytes[1] & 0x08)                              // LSB bits 0-3 contain the fractional part
        T += 0.5;
    if (T_bytes[1] & 0x04)
        T += 0.25;
    if (T_bytes[1] & 0x02)
        T += 0.125;
    if (T_bytes[1] & 0x01)
        T += 0.0625;

    return is_negative ? -T : T;
}
