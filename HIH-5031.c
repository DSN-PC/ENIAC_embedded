/*********************************************************************
 *
 *          Honeywell HIH-5031 humidity sensor functions
 *
 *********************************************************************
 * FileName:        	HIH-5031.c
 * Dependencies:	Honeywell HIH-5031 humidity sensor
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.46 or higher
 *
 * Company:
 *
 * Author				Date			Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vas Adam                             09/07/12		Created
 *********************************************************************/

#include <adc.h>

/****************************************************************************
  Function:
    float ReadHumidityHIH5031(float temperature)

  Description:
    This routine is used to read the humidity value
    from the Honeywell HIH-5031 analog sensor.

  Precondition:
    ADC is initialized

  Parameters:
    temperature (for compensation)

  Returns:
    Relative humidity (RH%)

  Remarks:
    None
  ***************************************************************************/
float ReadHumidityHIH5031(float temperature)
{
    float sensorRH;    // raw RH%

    ConvertADC();
    while (BusyADC());

    /*************************************************************************
     * Vout = (ReadADC()*Vsupply)/1023 : ADC output normalized,              *
     * Vout = Vsupply(0.00636(Sensor RH%) + 0.1515): HIH-5031 output formula *
     * => sensor RH% = (Vout / Vsupply - 0.1515) / 0.00636;                  *
     * Simplified formula:                                                   *
     *************************************************************************/
    sensorRH = ReadADC() * 0.1536 - 23.8207;
    return (sensorRH / (1.0546 - 0.00216 * temperature)); // temperature comensated RH%
}
