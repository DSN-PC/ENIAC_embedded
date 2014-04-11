/*********************************************************************
 *
 *                      ENIAC node UDP client
 *
 *********************************************************************
 * FileName:        	NodeUDPClient.c
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

#define SEND_BUFFER_SIZE    (2*sizeof(INT32))
#define RECEIVE_BUFFER_SIZE (sizeof(float))

static struct
{
    DataTypes dataType;
    INT32 step;
    NodeDescriptor* ndPtr;            // pointer to server node descriptor
    float* nvPtr;          // output pointer
} requestParams[NUM_NEIGHBORS];

static volatile BOOL start[NUM_NEIGHBORS];
static volatile BOOL close[NUM_NEIGHBORS];

static enum
{
    SOCKET_CLOSED,
    CREATE_SOCKET,
    INIT_REQUEST,
    SEND_REQUEST,
    RECEIVE_RESPONSE,
    PROCESS_RESPONSE,
    DONE
} nodeUDPClientStates[NUM_NEIGHBORS] = {SOCKET_CLOSED, SOCKET_CLOSED, SOCKET_CLOSED, SOCKET_CLOSED};


/*****************************************************************************
  Function:
	void NodeUDPClient(void)

  Summary:
	Implements a simple UDP client.

  Description:
	This function implements a UDP client.
	It is called periodically by EniacNode. It sends a request
        (dataType, step) to a neighbor node and receives the response.

  Precondition:
	UDP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
void NodeUDPClient(void)
{
    static SOCKET requesterSockets[NUM_NEIGHBORS];
    static struct sockaddr_in saddr[NUM_NEIGHBORS];
    static BYTE sendBuffers[NUM_NEIGHBORS][SEND_BUFFER_SIZE];
    static BYTE receiveBuffers[NUM_NEIGHBORS][RECEIVE_BUFFER_SIZE];
    static float* neighborValuePtrs[NUM_NEIGHBORS];
    static DWORD timers[NUM_NEIGHBORS];

    Neighbors n;
    for (n=0; n<=NUM_NEIGHBORS; n++)
    {
        switch (nodeUDPClientStates[n])
        {
            case SOCKET_CLOSED:
                if (!start[n])
                    break;
                
                nodeUDPClientStates[n] = CREATE_SOCKET;
                start[n] = FALSE;
                // Do not break here

            case CREATE_SOCKET:
                if ( (requesterSockets[n] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET )
                    break;               
                nodeUDPClientStates[n] = INIT_REQUEST;
                // Do not break here

            case INIT_REQUEST:
                saddr[n].sin_family = AF_INET;
                saddr[n].sin_addr.s_addr = requestParams[n].ndPtr->address.Val;
                saddr[n].sin_port = requestParams[n].ndPtr->port;
                *(INT32*)sendBuffers[n] = requestParams[n].dataType;
                *(INT32*)(sendBuffers[n]+sizeof(INT32)) = requestParams[n].step;
                neighborValuePtrs[n] = requestParams[n].nvPtr;

                nodeUDPClientStates[n] = SEND_REQUEST;
                // Do not break here

            case SEND_REQUEST:
                if ( sendto(requesterSockets[n], (const char*)sendBuffers[n], sizeof(sendBuffers[n]), 0, (struct sockaddr*)&saddr[n], sizeof(struct sockaddr_in)) < (int)sizeof(sendBuffers[n]) )
                    break;

                timers[n] = TickGet();
                nodeUDPClientStates[n] = RECEIVE_RESPONSE;
                break;

            case RECEIVE_RESPONSE:
                if ( recv(requesterSockets[n], (char*)receiveBuffers[n], sizeof(receiveBuffers[n]), 0) < (int)sizeof(receiveBuffers[n]) )
                {
                    if(TickGet()-timers[n] > 3*TICK_SECOND)
                        nodeUDPClientStates[n] = SEND_REQUEST;
                    break;
                }

                timers[n] = TickGet();                
                nodeUDPClientStates[n] = PROCESS_RESPONSE;
                // Do not break here

            case PROCESS_RESPONSE:
                if (isNaN(*(float*)receiveBuffers[n]))
                {
                    if(TickGet()-timers[n] > TICK_SECOND)
                        nodeUDPClientStates[n] = SEND_REQUEST;
                    break;
                }
                *neighborValuePtrs[n] = *(float*)receiveBuffers[n];
                
                nodeUDPClientStates[n] = DONE;
                // Do not break here

            case DONE:
                if (start[n])
                {
                    start[n] = FALSE;
                    nodeUDPClientStates[n] = INIT_REQUEST;
                }
                else if (close[n])
                {
                    closesocket(requesterSockets[n]);
                    nodeUDPClientStates[n] = SOCKET_CLOSED;
                }
                break;
        }
    }
}



/*****************************************************************************
  Function:
	void startNodeUDPClient(Neighbors n, DataTypes dt, INT32 step, NodeDescriptor* ndPtr, float* neighborValuePtr)

  Summary:
        Starts a UDP client.

  Description:
	This function is used for initializing and starting a UDP client.

  Precondition:
	UDP is initialized.

  Parameters:
        n - neighbor's direction
        dt - type of the requested data value
        step - the step of the requested data value
        ndPtr - pointer to the node descriptor structure
        nvPtr - pointer to the neighbor value (output parameter)
        
  Returns:
        None
  ***************************************************************************/
void startNodeUDPClient(Neighbors n, DataTypes dt, INT32 step, NodeDescriptor* ndPtr, float* nvPtr)
{
    if (nodeUDPClientFinished(n))
    {
        requestParams[n].dataType = dt;
        requestParams[n].step = step;
        requestParams[n].ndPtr = ndPtr;
        requestParams[n].nvPtr = nvPtr;
        start[n] = TRUE;
    }
}



/*****************************************************************************
  Function:
	BOOL nodeUDPClientFinished(Neighbors n)

  Summary:
        Returns the status of a given UDP client.

  Description:
	This function is used for checking if the UDP client of neighbor n has finished.

  Precondition:
        None

  Parameters:
        n - direction of the neighbor

  Returns:
        TRUE if the client has finished (or hasn't started yet)
        FALSE otherwise
  ***************************************************************************/
BOOL nodeUDPClientFinished(Neighbors n)
{
    return ( (nodeUDPClientStates[n] == SOCKET_CLOSED) || (nodeUDPClientStates[n] == DONE));
}



/*****************************************************************************
  Function:
	void closeNodeUDPClient(void)

  Summary:
        Closes a UDP client.

  Description:
	This function is used for closing the node's UDP client of neighbor n.

  Precondition:
	None

  Parameters:
        n - direction of the neighbor

  Returns:
        None
  ***************************************************************************/
void closeNodeUDPClient(Neighbors n)
{
    close[n] = TRUE;
}
