/*********************************************************************
 *
 *	Temperature, humidity and air pressure sensor functions
 *
 *********************************************************************
 * FileName:        	Sensors.c
 * Dependencies:	none
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


/* Function Prototypes */
void InitSensorMPL3115A2(void);
float ReadTemperatureMCP9808(void);
float ReadTemperatureMPL3115A2(void);
float ReadPressureMPL3115A2(void);
float ReadHumidityHIH5031(float temperature);



/****************************************************************************
  Function:
    void InitSensors(void)

  Description:
    This routine is used to initialize the sensors.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void InitSensors(void)
{
    InitSensorMPL3115A2();
}



/****************************************************************************
  Function:
    float ReadTemperature(BYTE sensor)

  Description:
    This routine is used to read the temperature value
    from a temperature sensor.

  Precondition:
    None

  Parameters:
    None

  Returns:
    Temperature (°C)

  Remarks:
    None
  ***************************************************************************/
float ReadTemperature(BYTE sensor)
{
    switch (sensor)
    {
        case 0:
            return ReadTemperatureMPL3115A2();
        case 1:
            return ReadTemperatureMCP9808();
        default:
            return -9999.0;
    }
}



/****************************************************************************
  Function:
    float ReadPressure(void)

  Description:
    This routine is used to read the air pressure value
    from the barometer.

  Precondition:
    None

  Parameters:
    None

  Returns:
    Air pressure (mbar)

  Remarks:
    None
  ***************************************************************************/
float ReadPressure(void)
{
    return ReadPressureMPL3115A2();
}



/****************************************************************************
  Function:
    float ReadHumidity(void)

  Description:
    This routine is used to read the humidity value
    from the humidity sensor.

  Precondition:
    None

  Parameters:
    None

  Returns:
    Relative humidity (RH%)

  Remarks:
    None
  ***************************************************************************/
float ReadHumidity(void)
{
    ReadHumidityHIH5031(ReadTemperature(1));
}
