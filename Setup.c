/*********************************************************************
 *
 *				Hardware Setup
 *
 *********************************************************************
 * FileName:        	Setup.c
 * Dependencies:	None
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.46 or higher
 *
 * Company:
 *
 * Author		Date            Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ing Manuel Malagon	1/03/11		Created
 * Vas Ádám             29/06/12        Modified for DSNPC_BOARD
 *********************************************************************/
#include <adc.h>
#include <i2c.h>
#include <timers.h>
#include <limits.h>

/* Include all headers for any enabled TCPIP Stack functions */
#include "TCPIP Stack\TCPIP.h"

/* Configuration bits */
#pragma config WDT=OFF, FOSC2=ON, FOSC=HSPLL, ETHLED=ON, XINST=OFF, \
               FCMEN=OFF, IESO=ON, CP0=OFF, STVR=OFF    \

/* Function Prototypes */
void InitSensors(void);

/* Global variables */
APP_CONFIG AppConfig;


/****************************************************************************
  Function:
    static void InitializeBoard(void)

  Description:
    This routine initializes the hardware.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void InitializeBoard(void)
{
    /* Enable 5× PLL, ÷3 Prescaler -> 41.667 MHz clock frequency with a 25 MHz oscillator */
    OSCTUNE = 0x40;

    /* Enable interrupts and priorities */
    RCONbits.IPEN = 1;              // Enable interrupt priority
    INTCONbits.GIEH = 1;            // Enable HIGH Priority Interrupts
    INTCONbits.GIEL = 1;            // Enable LOW Priority Interrupts

    /* Set up Timer2 */
    OpenTimer2( TIMER_INT_ON &      // Enable Timer2 interrupt
                T2_PS_1_16 &        // 1:16 prescaler
                T2_POST_1_8 );      // 1:8 postscaler
    IPR1bits.TMR2IP = 0;            // Low interrupt priority

    /* Set push button pin to input */
    BUTTON_TRIS = 1;

    /* Set 7-segment display pins to output */
    DISP_SEG_TRIS = 0;
    DISP_DG_TRIS = 0xF0;

    /* Set up ADC module. */
    OpenADC( ADC_FOSC_32 &
             ADC_RIGHT_JUST &
             ADC_20_TAD,
             ADC_CH2 &
             ADC_INT_OFF &
             ADC_REF_VDD_VSS,
             ADC_3ANA );

    /* Calibrate ADC. */
    ADC_CALIB();
    ConvertADC();
    while (BusyADC());
    ADC_NO_CALIB();

    /* Set up I2C module. */
    OpenI2C(MASTER, SLEW_ON);       // Master, Slew rate control \
                                       is enabled for High-Speed mode (400 kHz)
    SSP1ADD = (UINT8)(GetSystemClock()/400000ul/4); // 400 kHz, Clock = Fosc/(4 * (SSPADD + 1))

    InitSensors();
}


/****************************************************************************
  Function:
    void InitAppConfig(void)

  Description:
    Writes/Reads non-volatile config variables.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void InitAppConfig(void)
{
    char buffer[(sizeof(int)*CHAR_BIT)/3+3];   // Buffer for itoa() conversion
    int size_left;

    memset((void*)&AppConfig, 0x00, sizeof(AppConfig));

    AppConfig.MyMACAddr.v[0] = MY_DEFAULT_MAC_BYTE1;
    AppConfig.MyMACAddr.v[1] = MY_DEFAULT_MAC_BYTE2;
    AppConfig.MyMACAddr.v[2] = MY_DEFAULT_MAC_BYTE3;
    AppConfig.MyMACAddr.v[3] = MY_DEFAULT_MAC_BYTE4;
    AppConfig.MyMACAddr.v[4] = MY_DEFAULT_MAC_BYTE5;
    AppConfig.MyMACAddr.v[5] = MY_DEFAULT_MAC_BYTE6;

    AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
    AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
    AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
    AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
    AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
    AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
    AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;

    /* Format NetBIOSName, e.g. WSN_BOARD_3 (host name + "_" + board ID) */
    memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
    if ( (size_left = 16-(int)strlen(AppConfig.NetBIOSName)) >= 2 )
        strncatpgm2ram(AppConfig.NetBIOSName, "_", size_left);
    if ( (size_left = 16-(int)strlen(AppConfig.NetBIOSName)) >= 2 )
        strncat(AppConfig.NetBIOSName, itoa(DSNPC_BOARD_ID, buffer), size_left);
    FormatNetBIOSName(AppConfig.NetBIOSName);
}
