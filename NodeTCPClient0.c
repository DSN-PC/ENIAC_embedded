/*********************************************************************
 *
 *           ENIAC node TCP client 0 (for position and grid data)
 *
 *********************************************************************
 * FileName:        	NodeTCPClient0.c
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

#include "ENIAC.h"

#define SEND_BUFFER_SIZE    (sizeof(BYTE)+2*sizeof(float)+sizeof(WORD))
#define RECEIVE_BUFFER_SIZE (4*sizeof(INT32))

static struct
{
    float lat;                 // geographical latitude
    float lon;                 // geographical longitude
    NodeDescriptor* ndPtr;     // pointer to input/output structure (input: UDP server listening port, output: x,y coordinates)
    GridSize* gsPtr;           // pointer to output structure
} requestParams;

static volatile BOOL start;

static enum
{
    SOCKET_CLOSED,
    CREATE_SOCKET,
    CONNECT,
    SEND_REQUEST,
    RECEIVE_RESPONSE,
    CLOSE_SOCKET
} nodeTCPClient0State = SOCKET_CLOSED;



/*****************************************************************************
  Function:
	void NodeTCPClient0(void)

  Summary:
	Implements a TCP client for querying the main server for grid data.

  Description:
	This function implements a TCP client used for querying the main server
        for the node's (x,y) coordinates and the grid size.
	The function is called periodically by EniacNode.

  Precondition:
	TCP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
void NodeTCPClient0(void)
{
    static SOCKET requesterSocket;

    switch (nodeTCPClient0State)
    {
        case SOCKET_CLOSED:
            if (start)
            {
                nodeTCPClient0State = CREATE_SOCKET;
                start = FALSE;
                // Do not break here
            }
            else
                break;

        case CREATE_SOCKET:
            requesterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (requesterSocket == INVALID_SOCKET)
                break;
            
            nodeTCPClient0State = CONNECT;
            // Do not break here

        case CONNECT:
        {
            struct sockaddr_in saddr;
            int saddrlen = sizeof(struct sockaddr_in);
            saddr.sin_family = AF_INET;
            saddr.sin_addr.S_un.S_addr = mainServerAddress.Val;
            saddr.sin_port = mainServerPort;
            memset((void*)&saddr.sin_zero, 0x00, sizeof(saddr.sin_zero));

            if( connect(requesterSocket, (struct sockaddr*)&saddr, saddrlen) < 0 )
            	break;

            nodeTCPClient0State = SEND_REQUEST;
            // Do not break here
        }

        case SEND_REQUEST:
        {
            BYTE sendBuffer[SEND_BUFFER_SIZE];
            WORD udpListeningPort = swaps(requestParams.ndPtr->port);

            memset(sendBuffer, GET_MY_XY_AND_GRIDSIZE, sizeof(BYTE));
            memcpy(sendBuffer+sizeof(BYTE), (const void*)&requestParams.lat, sizeof(float));
            memcpy(sendBuffer+sizeof(BYTE)+sizeof(float), (const void*)&requestParams.lon, sizeof(float));
            memcpy(sendBuffer+sizeof(BYTE)+2*sizeof(float), (const void*)&udpListeningPort, sizeof(WORD));

            if ( send(requesterSocket, (const char*)sendBuffer, sizeof(sendBuffer), 0) < (int)sizeof(sendBuffer) )
                break;

            nodeTCPClient0State = RECEIVE_RESPONSE;
            break;
        }

        case RECEIVE_RESPONSE:
        {
            BYTE receiveBuffer[RECEIVE_BUFFER_SIZE];

            if ( recv(requesterSocket, (char*)receiveBuffer, sizeof(receiveBuffer), 0) < (int)sizeof(receiveBuffer) )
                break;

            requestParams.gsPtr->width = *(INT32*)receiveBuffer;
            requestParams.gsPtr->height = *(INT32*)(receiveBuffer+sizeof(INT32));
            requestParams.ndPtr->x = *(INT32*)(receiveBuffer+2*sizeof(INT32));
            requestParams.ndPtr->y = *(INT32*)(receiveBuffer+3*sizeof(INT32));
            
            nodeTCPClient0State = CLOSE_SOCKET;
            // Do not break here
        }

        case CLOSE_SOCKET:
            closesocket(requesterSocket);
            nodeTCPClient0State = SOCKET_CLOSED;
            break;
    }
}



/*****************************************************************************
  Function:
	BOOL startNodeTCPClient0(float lat, float lon, NodeDescriptor* ndPtr, GridSize* gsPtr)

  Summary:
        Starts TCP client 0.

  Description:
	This function is used for initializing and starting the TCP client 0.

  Precondition:
	TCP is initialized.

  Parameters:
        lat - geographical latitude
        lon - geographical longitude
        ndPtr - pointer to the node descriptor structure (output variable)
        gsPtr - pointer to the grid size structure (output variable)

  Returns:
        TRUE if the client started successfully
        FALSE otherwise
  ***************************************************************************/
BOOL startNodeTCPClient0(float lat, float lon, NodeDescriptor* ndPtr, GridSize* gsPtr)
{
    if (nodeTCPClient0Finished())
    {
        requestParams.lat = lat;
        requestParams.lon = lon;
        requestParams.ndPtr = ndPtr;
        requestParams.gsPtr = gsPtr;
        start = TRUE;
        return TRUE;
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	BOOL nodeTCPClient0Finished(void)

  Summary:
        Returns the status of the TCP client 0.

  Description:
	This function is used for checking if the TCP client 0 has finished.

  Precondition:
        None

  Parameters:
        None

  Returns:
        TRUE if the client has finished (or hasn't started yet)
        FALSE otherwise
  ***************************************************************************/
BOOL nodeTCPClient0Finished(void)
{
    return (nodeTCPClient0State == SOCKET_CLOSED);
}
