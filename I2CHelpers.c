/*********************************************************************
 *
 *                      I2C helper functions
 *
 *********************************************************************
 * FileName:        	I2CHelpers.c
 * Dependencies:	none
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.34 or higher
 *
 * Company:
 *
 * Author				Date			Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vas Ádám                             09/07/12		Created
 *********************************************************************/

#include <i2c.h>
#include "GenericTypeDefs.h"


/****************************************************************************
  Function:
    void I2CRegWrite(BYTE address, BYTE reg, BYTE val)

  Description:
    This routine is used to write a single byte into a register of an I2C peripheral.

  Precondition:
    I2C is initialized.

  Parameters:
    address - I2C Address
    reg - register address
    val - value to write

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void I2CRegWrite(BYTE address, BYTE reg, BYTE val)
{
    StartI2C();             // Send Start
        IdleI2C();
    WriteI2C(address);      // Send I2C "Write" Address
        IdleI2C();
    WriteI2C(reg);          // Send Register
        IdleI2C();
    WriteI2C(val);          // Send Value
        IdleI2C();
    StopI2C();              // Send Stop
}


/****************************************************************************
  Function:
    void I2CRegWriteN(BYTE address, BYTE reg1, BYTE n, BYTE *array)

  Description:
    This routine is used to write multiple bytes into a register of an I2C peripheral.

  Precondition:
    I2C is initialized.

  Parameters:
    address - I2C Address
    reg1 - register address
    n - number of bytes to write
    array - values to be written

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void I2CRegWriteN(BYTE address, BYTE reg1, BYTE n, BYTE *array)
{
    StartI2C();             // Send Start
        IdleI2C();
    WriteI2C(address);      // Send I2C "Write" Address
        IdleI2C();
    WriteI2C(reg1);         // Send Register
        IdleI2C();

    while (n>0)             // Write n values
    {
        WriteI2C(*array);   // Write value
            IdleI2C();
        array++;
        n--;
    }

    StopI2C();              // Send Stop
}


/****************************************************************************
  Function:
    BYTE I2CRegRead(BYTE address, BYTE reg)

  Description:
    This routine is used to read one byte from a register of an I2C peripheral.

  Precondition:
    I2C is initialized.

  Parameters:
    address - I2C Address
    reg - register address

  Returns:
    The first byte stored in the given register

  Remarks:
    None
  ***************************************************************************/
BYTE I2CRegRead(BYTE address, BYTE reg)
{
    static BYTE b;

    StartI2C();             // Send Start
        IdleI2C();
    WriteI2C(address);      // Send I2C "Write" Address
        IdleI2C();
    WriteI2C(reg);          // Send Register
        IdleI2C();
    RestartI2C();           // Send Repeat Start
        IdleI2C();
    WriteI2C(address+1);    // Send I2C "Read" Address
        IdleI2C();

    b = ReadI2C();          // Read Register Value
        IdleI2C();
    StopI2C();              // Send Stop

    return b;
}


/****************************************************************************
  Function:
    void I2CRegReadN(BYTE address, BYTE reg1, BYTE n, BYTE *array)

  Description:
    This routine is used to read multiple bytes from a register of an I2C peripheral.

  Precondition:
    I2C is initialized.

  Parameters:
    address - I2C Address
    reg1 - register address
    n - number of bytes to read
    array - array to store the read values

  Returns:
    The value stored in the given register

  Remarks:
    None
  ***************************************************************************/
void I2CRegReadN(BYTE address, BYTE reg1, BYTE n, BYTE *array)
{
    static BYTE b;

    StartI2C();             // Send Start
        IdleI2C();
    WriteI2C(address);      // Send I2C "Write" Address
        IdleI2C();
    WriteI2C(reg1);         // Send Register
        IdleI2C();
    RestartI2C();           // Send Repeat Start
        IdleI2C();
    WriteI2C(address+1);    // Send I2C "Read" Address
        IdleI2C();

    while (n>1)             // Read n-1 Register Values
    {
        b = ReadI2C();      // Read value
            IdleI2C();
        AckI2C();           // Send ACK
            IdleI2C();

        *array++ = b;       // Store value in the array
        n--;
    }
    b = ReadI2C();          // Read Last value
        IdleI2C();
    NotAckI2C();            // Send NACK
        IdleI2C();

    *array = b;             // Store last value in the array

    StopI2C();              // Send Stop
}
