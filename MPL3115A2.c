/*********************************************************************
 *
 *       Freescale MPL3115A2 digital digital barometer functions
 *
 *********************************************************************
 * FileName:        	MPL3115A2.c
 * Dependencies:	Freescale MPL3115A2 digital digital barometer
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.34 or higher
 *
 * Company:
 *
 * Author				Date			Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vas �d�m                             09/07/12		Created
 *********************************************************************/

#include "Tick.h"

/* MPL3115A2 register addresses */
#define MPL_ADDRESS         0xC0	// MPL3115A2 I2C Address
#define MPL_STATUS          0x00	// Sensor Status Register
#define MPL_OUT_P_MSB       0x01	// Bits 12-19 of 20-bit real-time Pressure sample
#define MPL_OUT_T_MSB       0x04	// Bits 4-11 of 12-bit real-time Temperature sample
#define MPL_CTRL_REG1       0x26        // Control register 1 (Modes, Oversampling)

/* Function Prototypes */
void I2CRegWrite(BYTE address, BYTE reg, BYTE val);
BYTE I2CRegRead(BYTE address, BYTE reg);
void I2CRegReadN(BYTE address, BYTE reg1, BYTE n, BYTE *array);

/* This variable is used to measure the time elapsed since the last
 * Temperature and/or Pressure acquisition.
 * It is initialized to maximum to make sure it doesn't prevent acquisition
 * when ReadTemperature() or ReadPressure() are called for the first time */
static DWORD Timer = -1;

/****************************************************************************
  Function:
    void InitSensorMPL3115A2(void)

  Description:
    This routine is used to initialize the MPL3115A2 sensor.

  Precondition:
    I2C module initialized

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void InitSensorMPL3115A2 (void)
{
    I2CRegWrite(MPL_ADDRESS, MPL_CTRL_REG1, 0x20);  // Set to Barometer mode with an OSR = 16
}



/****************************************************************************
  Function:
    float ReadTemperatureMPL3115A2(void)

  Description:
    This routine is used to read the temperature value
    from the Freescale MPL3115A2 digital I2C barometer.

  Precondition:
    None

  Parameters:
    None

  Returns:
    Temperature (°C)

  Remarks:
    None
  ***************************************************************************/
float ReadTemperatureMPL3115A2 (void)
{
    BYTE T_bytes[2],  // Temperature MSB, LSB
                ctrl_reg1;
    BOOL is_negative;
    float T;          // Temperature value in �C

    /* Setting the OST bit initiates acquisition of both temperature and pressure.
       If the last acquisition finished 1 second ago or later, don't initiate a new one.
       This way a few 100 milliseconds can be saved. */
    if (TickGet()-Timer > TICK_SECOND)
    {
        /* Make sure that OST = 0 before setting it */
        do
        {
            ctrl_reg1 = I2CRegRead(MPL_ADDRESS, MPL_CTRL_REG1);
        } while (ctrl_reg1 & 0x02);

        /* Set OST bit to initiate acquisition */
        I2CRegWrite(MPL_ADDRESS, MPL_CTRL_REG1, ctrl_reg1 | 0x02);

        /* Since OST is auto-clear, again wait for OST = 0 */
        do
        {
            ctrl_reg1 = I2CRegRead(MPL_ADDRESS, MPL_CTRL_REG1);
        } while (ctrl_reg1 & 0x02);

        /* Update Timer */
        Timer = TickGet();
    }

    /* Read 2 bytes of Temperature */
    I2CRegReadN(MPL_ADDRESS, MPL_OUT_T_MSB, 2, T_bytes);

    /* MSB contains the integer part */
    if (T_bytes[0] & 0x80)      // T < 0�C
    {
        is_negative = TRUE;
        T = (T_bytes[0] ^ 0xFF) + 1;
    }
    else
    {
        is_negative = FALSE;
        T = T_bytes[0];
    }

    /* Add fractional part from LSB bits 4-7. */
    if (T_bytes[1] & 0x80)      
        T += 0.5;
    if (T_bytes[1] & 0x40)
        T += 0.25;
    if (T_bytes[1] & 0x20)
        T += 0.125;
    if (T_bytes[1] & 0x10)
        T += 0.0625;

    return is_negative ? -T : T;
}


/****************************************************************************
  Function:
    float ReadPressureMPL3115A2(void)

  Description:
    This routine is used to read the pressure value
    from the Freescale MPL3115A2 digital I2C barometer.

  Precondition:
    Compensation coefficients are read from the MPL115A2 sensor

  Parameters:
    None

  Returns:
    Pressure (mbar)

  Remarks:
    None
  ***************************************************************************/
float ReadPressureMPL3115A2 (void)
{
    BYTE P_bytes[2],  // Temperature MSB, LSB
         ctrl_reg1;
    float P;

    /* Setting the OST bit initiates acquisition of both temperature and pressure.
       If the last acquisition finished 1 second ago or later, don't initiate a new one.
       This way a few 100 milliseconds can be saved. */
    if (TickGet()-Timer > TICK_SECOND)
    {
        /* Make sure that OST = 0 before setting it */
        do
        {
            ctrl_reg1 = I2CRegRead(MPL_ADDRESS, MPL_CTRL_REG1);
        } while (ctrl_reg1 & 0x02);

        /* Set OST bit to initiate acquisition */
        I2CRegWrite(MPL_ADDRESS, MPL_CTRL_REG1, ctrl_reg1 | 0x02);

        /* Since OST is auto-clear, again wait for OST=0 */
        do
        {
            ctrl_reg1 = I2CRegRead(MPL_ADDRESS, MPL_CTRL_REG1);
        } while (ctrl_reg1 & 0x02);

        /* Update Timer */
        Timer = TickGet();
    }

    /* Read 3-byte pressure value */
    I2CRegReadN(MPL_ADDRESS, MPL_OUT_P_MSB, 3, P_bytes);
    /* Get integer part contained by MSB, CSB and bits 6-7 of LSB.
       Bits 0-5 of LSB don't contain integer part, so right shift it by 6 bits. */
    P = ( ((UINT32)P_bytes[0] << 16) +
          ((UINT32)P_bytes[1] << 8) +
          ((UINT32)P_bytes[2] & 0xC0)
        ) >> 6;

    /* Add fractional part from LSB bits 4-5 */
    if (P_bytes[2] & 0x20)
        P += 0.5;
    if (P_bytes[2] & 0x10)
        P += 0.25;

    /* Value is in Pascals, so divide it by 100 */
    return P/100;
}
