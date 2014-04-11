/*********************************************************************
 *
 *         ENIAC node TCP client 1 (for neighbor descriptors)
 *
 *********************************************************************
 * FileName:        	NodeTCPClient1.c
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

#define SEND_BUFFER_SIZE       (sizeof(BYTE)+2*sizeof(INT32))
#define RECEIVE_BUFFER_1_SIZE  sizeof(IP_ADDR)
#define RECEIVE_BUFFER_2_SIZE  sizeof(WORD)

static struct
{
    NodeDescriptor* ndPtr;     // pointer to input/output structure (input fields: x,y coordinates, output fields: IP address, port)
} requestParams;

static volatile BOOL start = FALSE;
static volatile BOOL close = FALSE;

static enum
{
    SOCKET_CLOSED,
    CREATE_SOCKET,
    CONNECT,
    SEND_REQUEST,
    RECEIVE_ADDRESS,
    RECEIVE_PORT,
    CLOSE_SOCKET
} nodeTCPClient1State = SOCKET_CLOSED;



/*****************************************************************************
  Function:
	void NodeTCPClient1(void)

  Summary:
	Implements a TCP client for querying the main server for a neighbor's descriptor.

  Description:
	This function implements a TCP client used for querying the main server
        for a neighbor's descriptor.
	The function is called periodically by EniacNode.

  Precondition:
	TCP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
void NodeTCPClient1(void)
{
    static SOCKET requesterSocket;

    switch (nodeTCPClient1State)
    {
        case SOCKET_CLOSED:
            if (start)
            {
                nodeTCPClient1State = CREATE_SOCKET;
                start = FALSE;
                // Do not break here
            }
            else
                break;

        case CREATE_SOCKET:
            requesterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (requesterSocket == INVALID_SOCKET)
                break;
            nodeTCPClient1State = CONNECT;
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
            	return;

            nodeTCPClient1State = SEND_REQUEST;
            // Do not break here
        }

        case SEND_REQUEST:
        {
            BYTE sendBuffer[SEND_BUFFER_SIZE];          

            memset(sendBuffer, GET_NEIGHBOR_ADDRESS_AND_PORT, sizeof(BYTE));
            memcpy(sendBuffer+sizeof(BYTE), (const void*)&requestParams.ndPtr->x, sizeof(INT32));
            memcpy(sendBuffer+sizeof(BYTE)+sizeof(INT32), (const void*)&requestParams.ndPtr->y, sizeof(INT32));

            if ( send(requesterSocket, (const char*)sendBuffer, sizeof(sendBuffer), 0) < (int)sizeof(sendBuffer) )
                break;

            nodeTCPClient1State = RECEIVE_ADDRESS;
            break;
        }
        
        case RECEIVE_ADDRESS:
        {
            BYTE receiveBuffer[RECEIVE_BUFFER_1_SIZE];            
            if ( (recv(requesterSocket, (char*)receiveBuffer, sizeof(receiveBuffer), 0) < (int)sizeof(receiveBuffer)) ||
                 ((receiveBuffer[0] == 0xff) &&
                  (receiveBuffer[1] == 0xff) &&
                  (receiveBuffer[2] == 0xff) &&
                  (receiveBuffer[3] == 0xff)))
            {
                break;
            }
            requestParams.ndPtr->address = *(IP_ADDR*)(receiveBuffer);
            
            nodeTCPClient1State = RECEIVE_PORT;
            break;
        }
            
        case RECEIVE_PORT:
        {
            BYTE receiveBuffer[RECEIVE_BUFFER_2_SIZE];            
            if ( recv(requesterSocket, (char*)receiveBuffer, sizeof(receiveBuffer), 0) < (int)sizeof(receiveBuffer) )
                break;            
            requestParams.ndPtr->port = swaps(*(WORD*)(receiveBuffer));

            nodeTCPClient1State = CLOSE_SOCKET;
            // Do not break here
        }
        
        case CLOSE_SOCKET:
            closesocket(requesterSocket);
            nodeTCPClient1State = SOCKET_CLOSED;
            break;
    }
}



/*****************************************************************************
  Function:
	BOOL startNodeTCPClient1(NodeDescriptor* ndPtr)

  Summary:
        Starts TCP client 1.

  Description:
	This function is used for initializing and starting the TCP client 1.

  Precondition:
	TCP is initialized.

  Parameters:
        ndPtr - pointer to the neighbor descriptor structure (output variable)

  Returns:
        TRUE if the client started successfully
        FALSE otherwise
  ***************************************************************************/
BOOL startNodeTCPClient1(NodeDescriptor* ndPtr)
{
    if (nodeTCPClient1Finished())
    {
        requestParams.ndPtr = ndPtr;
        start = TRUE;
        return TRUE;
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	BOOL nodeTCPClient1Finished(void)

  Summary:
        Returns the status of the TCP client 1.

  Description:
	This function is used for checking if the TCP client 1 has finished.

  Precondition:
        None

  Parameters:
        None

  Returns:
        TRUE if the client has finished (or hasn't started yet)
        FALSE otherwise
  ***************************************************************************/
BOOL nodeTCPClient1Finished(void)
{
    return (nodeTCPClient1State == SOCKET_CLOSED);
}
