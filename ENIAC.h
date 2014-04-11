/*********************************************************************
 *
 *                  Eniac macros and type definitions
 *
 *********************************************************************
 * FileName:        	Eniac.h
 * Dependencies:	None
 * Processor:       	PIC18
 * Compiler:        	Microchip C18 v3.46 or higher
 *
 * Company:
 *
 * Author		Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vas Ádám             02/09/13        Created
 *********************************************************************/
#include "TCPIP Stack/TCPIP.h"
#include "GenericTypeDefs.h"
#include "TCPIPConfig.h"

#define NAN                 (0./0.)

/* Set the address of the main server to the sender address of the incoming
 * discovery message (see Announce.c), so the deafult is 0.0.0.0 here.
 * If you modify these values, it is required to remove that functionality
 * from Announce.c otherwise the TCP client will get stuck at connect phase. */
#define MAIN_SERVER_DEFAULT_ADDRESS_BYTE1        (0ul)
#define MAIN_SERVER_DEFAULT_ADDRESS_BYTE2        (0ul)
#define MAIN_SERVER_DEFAULT_ADDRESS_BYTE3        (0ul)
#define MAIN_SERVER_DEFAULT_ADDRESS_BYTE4        (0ul)
extern IP_ADDR mainServerAddress;

#define MAIN_SERVER_DEFAULT_PORT    (30303u)
extern WORD mainServerPort;

/* TCP request types */
#define GET_MY_XY_AND_GRIDSIZE        (BYTE)0x00
#define GET_NEIGHBOR_ADDRESS_AND_PORT (BYTE)0x01

#define isNaN(value) (value != value)


/* types of exchanged data */
typedef enum
{
    Z = 0,      // geopotential height of the 500 mbar level
    DZDT,       // dz/dt
    XI,         // Laplace(z)
    DXIDT,      // dxi/dt
    ETA         // absolute vorticity
} DataTypes;

/* directions to close neighbours */
typedef enum
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST,
    NUM_NEIGHBORS
} Neighbors;

/* grid size structure */
typedef struct
{
    INT32 width;
    INT32 height;
} GridSize;

/* node descriptor structure */
typedef struct
{
    INT32 x;
    INT32 y;
    IP_ADDR address;
    WORD port;
} NodeDescriptor;


/***************************************************************************************************
                                       Function prototypes
 ***************************************************************************************************/
float getValue(DataTypes dataType, INT32 step);
void NodeUDPServer(void);
void startNodeUDPServer(NodeDescriptor* ndPtr);
BOOL nodeUDPServerListening(void);
void closeNodeUDPServer(void);
void NodeUDPClient(void);
void startNodeUDPClient(Neighbors n, DataTypes dt, INT32 step, NodeDescriptor* ndPtr, float* nvPtr);
BOOL nodeUDPClientFinished(Neighbors n);
void closeNodeUDPClient(Neighbors n);
void NodeTCPClient0(void);
BOOL startNodeTCPClient0(float lat, float lon, NodeDescriptor* ndPtr, GridSize* gsPtr);
BOOL nodeTCPClient0Finished(void);
void closeNodeTCPClient0(void);
void NodeTCPClient1(void);
BOOL startNodeTCPClient1(NodeDescriptor* ndPtr);
BOOL nodeTCPClient1Finished(void);
void closeNodeTCPClient1(void);
void SevenSegmentDisplay(int value);
