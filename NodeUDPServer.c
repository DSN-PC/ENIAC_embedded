/*********************************************************************
 *
 *                      ENIAC node UDP server
 *
 *********************************************************************
 * FileName:        	NodeUDPServer.c
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

#define RECEIVE_BUFFER_SIZE (2*sizeof(INT32))
#define SEND_BUFFER_SIZE    (sizeof(float))


/***************************************************************************************************
                                        Global variables
 ***************************************************************************************************/
static NodeDescriptor* nodeDescriptorPtr;
static volatile BOOL closeServer = TRUE;

static enum
{
    SOCKET_CLOSED,
    CREATE_SOCKET,
    BIND_SOCKET,
    RECEIVE_REQUEST,
    SEND_RESPONSE
} nodeUDPServerState = SOCKET_CLOSED;


/*****************************************************************************
  Function:
	void NodeUDPServer(void)

  Summary:
	Implements a UDP server to the Eniac node.

  Description:
	This function implements a UDP server.
	It is called periodically by EniacNode. It receives a request
        (dataType, step) from a client and sends a response containing
        the requested data.

  Precondition:
	UDP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
void NodeUDPServer(void)
{
    static SOCKET providerSocket;
    static BYTE sendBuffer[SEND_BUFFER_SIZE];

    static struct sockaddr_in caddr;    
    static int caddrlen = sizeof(struct sockaddr_in);
    static DWORD timer;

    switch (nodeUDPServerState)
    {
        case SOCKET_CLOSED:
            if (closeServer)
                break;
            
            nodeUDPServerState = CREATE_SOCKET;
            // Do not break here

        case CREATE_SOCKET:
            if ( (providerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET )
                break;
            
            nodeUDPServerState = BIND_SOCKET;
            // Do not break here

        case BIND_SOCKET:
        {
            struct sockaddr_in saddr;
            int saddrlen = sizeof(struct sockaddr_in);
            saddr.sin_family = AF_INET;
            saddr.sin_addr.s_addr = INADDR_ANY;
            saddr.sin_port = 0;
            memset((void*)&saddr.sin_zero, 0x00, sizeof(saddr.sin_zero));

            if ( bind(providerSocket, (struct sockaddr*)&saddr, saddrlen) == SOCKET_ERROR )
                break;

            /* Microchip's TCP/IP Stack doesn't have the function getsockname(),
               so this is a workaround to get the local port of the recently created server socket. */
            nodeDescriptorPtr->port = UDPSocketInfo[activeUDPSocket].localPort;
            
            timer = TickGet();

            nodeUDPServerState = RECEIVE_REQUEST;
            break;
        }

        case RECEIVE_REQUEST:
        {
            static BYTE receiveBuffer[RECEIVE_BUFFER_SIZE];
            
            if (recvfrom(providerSocket, (char*)receiveBuffer, sizeof(receiveBuffer), 0, (struct sockaddr*)&caddr, &caddrlen) < (int)sizeof(receiveBuffer))
            {
                if( closeServer && (TickGet()-timer > 32*TICK_SECOND) )
                {
                    closesocket(providerSocket);
                    nodeUDPServerState = SOCKET_CLOSED;
                }
                break;
            }
            
            *(float*)sendBuffer = getValue(*(INT32*)receiveBuffer, *(INT32*)(receiveBuffer+sizeof(INT32)));
            timer = TickGet();
            
            nodeUDPServerState = SEND_RESPONSE;
            // Do not break here
        }

        case SEND_RESPONSE:
            if ( sendto(providerSocket, (const char*)sendBuffer, sizeof(sendBuffer), 0, (struct sockaddr*)&caddr, caddrlen) < (int)sizeof(sendBuffer) )
                break;

            nodeUDPServerState = RECEIVE_REQUEST;
            break;
    }
}



/*****************************************************************************
  Function:
	void startNodeUDPServer(NodeDescriptor* ndPtr)

  Summary:
        Starts UDP server.

  Description:
	This function is used for initializing and starting the UDP server.

  Precondition:
	UDP is initialized.

  Parameters:
        ndPtr - pointer to the node descriptor structure (output parameter)
                used for storing the local port of the recently created UDP server socket

  Returns:
        None
  ***************************************************************************/
void startNodeUDPServer(NodeDescriptor* ndPtr)
{
    nodeDescriptorPtr = ndPtr;
    closeServer = FALSE;
}



/*****************************************************************************
  Function:
	BOOL nodeUDPServerListening(void)

  Summary:
        Returns the status of the UDP server.

  Description:
	This function is used for checking if the UDP server is already listening.

  Precondition:
        None

  Parameters:
        None

  Returns:
        TRUE if the server is listening
        FALSE otherwise
  ***************************************************************************/
BOOL nodeUDPServerListening(void)
{
    return (nodeUDPServerState >= RECEIVE_REQUEST);
}



/*****************************************************************************
  Function:
	void closeNodeUDPServer(void)

  Summary:
        Closes UDP server.

  Description:
	This function is used for closing the node's UDP server.

  Precondition:
	None

  Parameters:
        None

  Returns:
        None
  ***************************************************************************/
void closeNodeUDPServer(void)
{
    closeServer = TRUE;
}
