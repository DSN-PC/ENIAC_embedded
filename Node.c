/*********************************************************************
 *
 *                      Eniac node calculations
 *
 *********************************************************************
 * FileName:        	EniacNode.c
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

#include <math.h>
#include <stdarg.h>
#include "ENIAC.h"

#define PI             3.1415927

/* geographical constants */
#define DS             736000ul                     // grid interval (736 km)
#define GRAV           9.80665                      // gravitational constant
#define OMEGA          ((2.0*PI)/(24.0*60.0*60.0))  // angular velocity of Earth's rotation
#define LAT            0.2790806                    // geographical latitude of the node
#define LON            -2.1375256                   // geographical longitude of the node
#define Z0             5808.756                     // initial value of z

/* constants required to the calculations
   NOTE: changing these parameters requires the modification of the linker script!
         (see eniac_datastructs)                                                   */
#define HOURS          24                           // forecast duration in hours
#define DT_SEC         3600                         // duration of one forecast step in seconds
#define NUM_ITERATIONS 200                          // number of iterations of the solution method of the Poisson-equation


/***************************************************************************************************
                                        Global variables
 ***************************************************************************************************/

/* IP address and port of the main server */
IP_ADDR mainServerAddress = MAIN_SERVER_DEFAULT_ADDRESS_BYTE1 | MAIN_SERVER_DEFAULT_ADDRESS_BYTE2<<8ul | MAIN_SERVER_DEFAULT_ADDRESS_BYTE3<<16ul | MAIN_SERVER_DEFAULT_ADDRESS_BYTE4<<24ul;
WORD mainServerPort = MAIN_SERVER_DEFAULT_PORT;

/* size of the grid */
GridSize gridSize;

/* variables indicating the position of the node in the grid */
static BOOL inner, northern, eastern, southern, western;
        
/* on a border node this variable indicates whether the fluid is entering or leaving the area */
static BOOL fluidLeaving;

/* geographical parameters */
static float m,                 // map projection magnification factor
             f,                 // Coriolis parameter
             h;                 // defined as g*(m^2)/f

/* data structures for calculation data */
#pragma udata ENIAC
static struct
{
    INT32 step;
    float dataArray[HOURS+1];
} z, xi;

static struct
{
    INT32 step;
    float dataArray[HOURS];
} dxidt, eta;

static struct
{
    INT32 step;
    float dataArray[NUM_ITERATIONS+1];
    BOOL denyNextStepRequests;
} dzdt;
#pragma udata

/* descriptor of this node */
NodeDescriptor descriptor;

/* neighbors' descriptors */
NodeDescriptor neighborDescriptors[4];

/* neighbors' current values (temporary buffer used during data exchange between neighbors) */
static float neighborValues[4];


/******************************************************************************
 *                           Function prototypes                              *
 ******************************************************************************/
static BOOL startUDPServer(void);
static BOOL initNode(void);
static BOOL calculateXI(INT32 step);
static BOOL checkIfFluidIsLeaving(INT32 step);
static BOOL extrapolateXI(INT32 step);
static BOOL calculateDXIDT(INT32 step);
static BOOL solvePoissonEquation(INT32 step);
static BOOL extrapolateDXIDT(INT32 step);
static void setValue(DataTypes dt, INT32 step, float data);
static void getNeighborsValuesUDP(DataTypes dt, INT32 step, int num_neighbors, ...);
static BOOL neighborsValuesUDPFinished(int num_neighbors, ...);
#define getNeighborValueUDP(n, dataType, step) startNodeUDPClient(n, dataType, step, &neighborDescriptors[n], &neighborValues[n])
#define getNeighborValue(n) (neighborValues[n])
#define getGridSizeAndPositionTCP() startNodeTCPClient0(LAT, LON, &descriptor, &gridSize)
#define gridTCPFinished() nodeTCPClient0Finished()
#define getNeighborDescriptorTCP(n) startNodeTCPClient1(&neighborDescriptors[n])
#define neighborDescriptorTCPFinished() nodeTCPClient1Finished()


/*****************************************************************************
  Function:
	BOOL EniacNode(void)

  Summary:
        Implements an ENIAC node.

  Description:
	This function implements a simulated ENIAC node.
	The function is called periodically by the stack until the calculation
        is finished.

  Precondition:
        None

  Parameters:
	None

  Returns:
        TRUE if prediction calculation has finished
        FALSE otherwise
******************************************************************************/
BOOL EniacNode(void)
{
    static INT32 step=0;
    static enum
    {
        INIT_NODE,
        CALCULATE_XI,
        CHECK_IF_FLUID_IS_LEAVING,
        EXTRAPOLATE_XI,
        CALCULATE_ETA,
        CALCULATE_DXIDT,
        SOLVE_POISSON_EQUATION,
        EXTRAPOLATE_DXIDT,
        STEP_FORWARD,
        MAIN_LOOP_FINISHED,
        DONE
    } eniacNodeState = INIT_NODE;

    /* Call TCP and UDP server and client tasks. */
    NodeTCPClient0();
    NodeTCPClient1();
    NodeUDPServer();
    NodeUDPClient();

    switch(eniacNodeState)
    {
        case INIT_NODE:
            if (!initNode())
                break;            

            if (!inner)
            {
                eniacNodeState = CHECK_IF_FLUID_IS_LEAVING;
                break;
            }
            eniacNodeState = CALCULATE_XI;
            // Do not break here

        /***************************
         *      INNER NODES:       *
         * Calculate xi=Laplace(z) *
         ***************************/
        case CALCULATE_XI:
            if (calculateXI(step))
                eniacNodeState = CALCULATE_ETA;
            break;

        /*****************************************
         *             BORDER NODES:             *
         * Calculate xi by extrapolation,        *
         * check if fluid is entering or leaving *
         *****************************************/
        case CHECK_IF_FLUID_IS_LEAVING:
            if (!checkIfFluidIsLeaving(step))
                break;
            eniacNodeState = EXTRAPOLATE_XI;
            // Do not break here

        case EXTRAPOLATE_XI:
            if (!extrapolateXI(step))
                break;
            eniacNodeState = CALCULATE_ETA;
            // Do not break here

        /****************************************************
         ****************************************************
         ************** MAIN LOOP STARTS HERE ***************
         ****************************************************
         ****************************************************/            
        /********************************
         * Calculate absolute vorticity *
         ********************************/
        case CALCULATE_ETA:
            setValue(ETA, step, h*getValue(XI, step) + f);
            
            if (inner)
                eniacNodeState = CALCULATE_DXIDT;
                // Do not break here
            else if (fluidLeaving)
            {
                eniacNodeState = EXTRAPOLATE_DXIDT;
                break;
            }
            else
            {
                eniacNodeState = STEP_FORWARD;
                break;
            }

        /*************************************
         *            INNER NODES:           *
         * Calculate dxi/dt = Jacobi(eta,z), *
         * Solve the Poisson equation        *
         *************************************/
        case CALCULATE_DXIDT:
            if (!calculateDXIDT(step))
                break;
            
            dzdt.step = 0;
            dzdt.denyNextStepRequests = FALSE;
            eniacNodeState = SOLVE_POISSON_EQUATION;
            // Do not break here

        case SOLVE_POISSON_EQUATION:
            if (solvePoissonEquation(step))
            {
                dzdt.denyNextStepRequests = TRUE;
                eniacNodeState = STEP_FORWARD;
            }
            break;

        /****************************************************
         *                  BORDER NODES:                   *
         * Fluid leaving: Calculate dxi/dt by extrapolation *
         ****************************************************/
        case EXTRAPOLATE_DXIDT:
            if (!extrapolateDXIDT(step))
                break;
            eniacNodeState = STEP_FORWARD;
            // Do not break here

        /*****************************************************************
         * Step forward xi and z based on dxi/dt �s dz/dt.               *
         * Note: dz/dt=0 at border nodes (initialized automatically) and *
         * dxi/dt=0 at border nodes where fluid is entering              *
         *****************************************************************/
        case STEP_FORWARD:
        {
            float xiNew, zNew;
            /* First step: forward differences */
            if (step==0)
            {
                xiNew = getValue(XI, step) + DT_SEC*getValue(DXIDT, step);
                zNew = getValue(Z, step) + DT_SEC*getValue(DZDT, NUM_ITERATIONS);
            }
            /* Next steps: central differences */
            else
            {
                xiNew = getValue(XI, step-1) + 2*DT_SEC*getValue(DXIDT, step);
                zNew = getValue(Z, step-1) + 2*DT_SEC*getValue(DZDT, NUM_ITERATIONS);
            }

            setValue(XI, step+1, xiNew);
            setValue(Z, step+1, zNew);
            
            SevenSegmentDisplay(zNew);

            if (++step == HOURS)
                eniacNodeState = MAIN_LOOP_FINISHED;
                // Do not break here
            else
            {
                eniacNodeState = CALCULATE_ETA;
                break;
            }
        }
            
        case MAIN_LOOP_FINISHED:
            closeNodeUDPServer();
            eniacNodeState = DONE;
            // Do not break here

        case DONE:
            return TRUE;
    }
    return FALSE;
}


/*****************************************************************************
  Function:
	static BOOL startUDPServer(void)

  Description:
	This function starts the UDP server of the node.

  Precondition:
        None

  Parameters:
	None

  Returns:
        TRUE if the UDP server started succesfully
        FALSE if the UDP server hasn't started yet
******************************************************************************/
static BOOL startUDPServer(void)
{
    static enum
    {
        START_UDP_SERVER,
        WAIT_FOR_LISTENING
    } startUDPServerState = START_UDP_SERVER;

    switch (startUDPServerState)
    {
        case START_UDP_SERVER:
            startNodeUDPServer(&descriptor);

            startUDPServerState = WAIT_FOR_LISTENING;
            break;

        case WAIT_FOR_LISTENING:
            if (!nodeUDPServerListening())
                break;

            startUDPServerState = START_UDP_SERVER;
            return TRUE;
    }
    return FALSE;
}


/*****************************************************************************
  Function:
	static BOOL initNode(void)

  Description:
	This function initializes the node.

  Precondition:
        None

  Parameters:
	None

  Returns:
        TRUE if the init process finished
        FALSE otherwise (in progress)
******************************************************************************/
static BOOL initNode(void)
{
    static enum
    {
        INIT_VARIABLES_1,
        START_UDP_SERVER,
        REQUEST_GRID_DATA,
        RECEIVE_GRID_DATA,
        INIT_VARIABLES_2,
        GET_NEIGHBORS_DESCRIPTORS
    } initNodeState = INIT_VARIABLES_1;

    switch (initNodeState)
    {
        case INIT_VARIABLES_1:
            /* Initialize geographical parameters */
            m = 2.0 / (1.0+sin(LAT));
            f = 2.0 * OMEGA * sin(LAT);
            h = GRAV * m*m / f;

            /* Initialize data structures */
            setValue(Z, 0, Z0);
            dzdt.step = xi.step = dxidt.step = eta.step = -1;

            initNodeState = START_UDP_SERVER;
            // Do not break here

        case START_UDP_SERVER:
            if (!startUDPServer())
                break;
            
            initNodeState = REQUEST_GRID_DATA;
            // Do not break here

        case REQUEST_GRID_DATA:
            if (getGridSizeAndPositionTCP())
                initNodeState = RECEIVE_GRID_DATA;
            break;

        case RECEIVE_GRID_DATA:
            if (!gridTCPFinished())
                break;

            initNodeState = INIT_VARIABLES_2;
            // Do not break here

        case INIT_VARIABLES_2:
            /* Check node position: inner/border node */
            if (descriptor.y == (gridSize.height-1))
                northern = TRUE;
            else if (descriptor.y == 0)
                southern = TRUE;
            if (descriptor.x == (gridSize.width-1))
                eastern = TRUE;
            else if (descriptor.x == 0)
                western = TRUE;
            inner = !northern && !eastern && !southern && !western;

            /* Set neighbors' positions */
            neighborDescriptors[NORTH].x = descriptor.x;
            neighborDescriptors[NORTH].y = northern ? descriptor.y-2 : descriptor.y+1;
            neighborDescriptors[EAST].x = eastern ? descriptor.x-2 : descriptor.x+1;
            neighborDescriptors[EAST].y = descriptor.y;
            neighborDescriptors[SOUTH].x = descriptor.x;
            neighborDescriptors[SOUTH].y = southern ? descriptor.y+2 : descriptor.y-1;
            neighborDescriptors[WEST].x = western ? descriptor.x+2 : descriptor.x-1;
            neighborDescriptors[WEST].y = descriptor.y;

            /* dz/dt=0 at border nodes (initialized automatically), but setting *
             * its step to max is required to make sure it doesn't return NaN   *
             * when an inner node asks for it during the solution method of the *
             * Poisson equation. (see getData() function).                      */
            if (!inner)
                dzdt.step = NUM_ITERATIONS;

            initNodeState = GET_NEIGHBORS_DESCRIPTORS;
            // Do not break here

        /* If this is a northern border node, then let the distant southern neighbor be the "northern neighbor".
           (This method is applied to eastern, western and southern border nodes, too.)
           This is required because the border nodes calculate their xi and dxi/dt values by extrapolation. */
        case GET_NEIGHBORS_DESCRIPTORS:
        {
            static enum
            {
                REQUEST_NORTHERN,
                RECEIVE_NORTHERN,
                REQUEST_EASTERN,
                RECEIVE_EASTERN,
                REQUEST_SOUTHERN,
                RECEIVE_SOUTHERN,
                REQUEST_WESTERN,
                RECEIVE_WESTERN
            } neighborDescriptorsState = REQUEST_NORTHERN;

            switch (neighborDescriptorsState)
            {
                case REQUEST_NORTHERN:
                    if (getNeighborDescriptorTCP(NORTH))
                        neighborDescriptorsState = RECEIVE_NORTHERN;
                    break;

                case RECEIVE_NORTHERN:
                    if (!neighborDescriptorTCPFinished())
                        break;

                    neighborDescriptorsState = REQUEST_EASTERN;
                    // Do not break here

                case REQUEST_EASTERN:
                    if (getNeighborDescriptorTCP(EAST))
                        neighborDescriptorsState = RECEIVE_EASTERN;
                    break;

                case RECEIVE_EASTERN:
                    if (!neighborDescriptorTCPFinished())
                        break;

                    neighborDescriptorsState = REQUEST_SOUTHERN;
                    // Do not break here
                
                case REQUEST_SOUTHERN:
                    if (getNeighborDescriptorTCP(SOUTH))
                        neighborDescriptorsState = RECEIVE_SOUTHERN;
                    break;

                case RECEIVE_SOUTHERN:
                    if (!neighborDescriptorTCPFinished())
                        break;

                    neighborDescriptorsState = REQUEST_WESTERN;
                    // Do not break here

                case REQUEST_WESTERN:
                    if (getNeighborDescriptorTCP(WEST))
                        neighborDescriptorsState = RECEIVE_WESTERN;
                    break;

                case RECEIVE_WESTERN:
                    if (!neighborDescriptorTCPFinished())
                        break;

                    neighborDescriptorsState = REQUEST_NORTHERN;
                    initNodeState = INIT_VARIABLES_1;
                    return TRUE;
            }
        }
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	static BOOL calculateXI(INT32 step)

  Description:
	This function is used for calculating XI.
        It queries its neighbors for Z values and then does the calculations.

  Precondition:
        node is initialized

  Parameters:
        step - current main iteration step

  Returns:
        TRUE if the calculation process finished
        FALSE otherwise (in progress)
******************************************************************************/
static BOOL calculateXI(INT32 step)
{
    static enum
    {
        REQUEST_NEIGHBORS_Z,
        RECEIVE_NEIGHBORS_Z,
        CALCULATE_XI
    } calculateXIState = REQUEST_NEIGHBORS_Z;

    switch (calculateXIState)
    {
        case REQUEST_NEIGHBORS_Z:
            getNeighborsValuesUDP(Z, step, NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST);
            
            calculateXIState = RECEIVE_NEIGHBORS_Z;
            break;

        case RECEIVE_NEIGHBORS_Z:
            if (!neighborsValuesUDPFinished(NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST))
                break;

            calculateXIState = CALCULATE_XI;
            // Do not break here

        case CALCULATE_XI:
        {
            float sum = 0;
            Neighbors n;
            /* xi(i,j)=(z(i+1,j)+z(i-1,j)+z(i,j+1)+z(i,j-1)-4*z)/(DS^2) */
            for (n=0; n<NUM_NEIGHBORS; n++)
                sum += getNeighborValue(n);
            setValue(XI, step, ((sum-4*getValue(Z, 0)) / DS) / DS);

            calculateXIState = REQUEST_NEIGHBORS_Z;
            return TRUE;
        }
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	static BOOL checkIfFluidIsLeaving(INT32 step)

  Description:
	This function is used for checking if the fluid is entering or leaving
        the area at this node.
        It queries its neighbors for Z values and then does the calculations.

  Precondition:
        node is initialized

  Parameters:
        step - current main iteration step

  Returns:
        TRUE if the checking process finished
        FALSE otherwise (in progress)
******************************************************************************/
static BOOL checkIfFluidIsLeaving(INT32 step)
{
    static enum
    {
        REQUEST_NEIGHBORS_Z,
        RECEIVE_NEIGHBORS_Z,
        CHECK_IF_FLUID_IS_LEAVING
    } checkIfFluidIsLeavingState = REQUEST_NEIGHBORS_Z;

    switch (checkIfFluidIsLeavingState)
    {
        case REQUEST_NEIGHBORS_Z:
            if (northern)
                getNeighborsValuesUDP(Z, step, 2, EAST, WEST);
            else if (eastern)
                getNeighborsValuesUDP(Z, step, 2, SOUTH, NORTH);
            else if (southern)
                getNeighborsValuesUDP(Z, step, 2, WEST, EAST);
            else if (western)
                getNeighborsValuesUDP(Z, step, 2, NORTH, SOUTH);

            checkIfFluidIsLeavingState = RECEIVE_NEIGHBORS_Z;
            break;

        case RECEIVE_NEIGHBORS_Z:
            if (northern)
            {
                if (!neighborsValuesUDPFinished(2, EAST, WEST))
                    break;
            }
            else if (eastern)
            {
                if (!neighborsValuesUDPFinished(2, SOUTH, NORTH))
                    break;
            }
            else if (southern)
            {
                if (!neighborsValuesUDPFinished(2, WEST, EAST))
                    break;
            }
            else if (western)
            {
                if (!neighborsValuesUDPFinished(2, NORTH, SOUTH))
                    break;
            }

            checkIfFluidIsLeavingState = CHECK_IF_FLUID_IS_LEAVING;
            // Do not break here

        case CHECK_IF_FLUID_IS_LEAVING:
            if (northern && (getNeighborValue(EAST) >= getNeighborValue(WEST)))
                fluidLeaving = TRUE;
            else if (eastern && (getNeighborValue(SOUTH) >= getNeighborValue(NORTH)))
                fluidLeaving = TRUE;
            else if (southern && (getNeighborValue(WEST) >= getNeighborValue(EAST)))
                fluidLeaving = TRUE;
            else if (western && (getNeighborValue(NORTH) >= getNeighborValue(SOUTH)))
                fluidLeaving = TRUE;

            /* dxi/dt=0 at border nodes (initialized automatically) where *
             * fluid is entering the area, but setting its step to max    *
             * is required so that it doesn't return NaN when a neighbor *
             * node asks for it during the calculation of eta.            */
            if (!fluidLeaving)
                dxidt.step = HOURS-1;
            
            checkIfFluidIsLeavingState = REQUEST_NEIGHBORS_Z;
            return TRUE;
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	static BOOL extrapolateXI(INT32 step)

  Description:
	This function is used for extrapolating the value of XI.
        It queries its neighbors for XI values and then does the calculations.

  Precondition:
        node is initialized

  Parameters:
        step - current main iteration step

  Returns:
        TRUE if the extrapolation process finished
        FALSE otherwise (in progress)
******************************************************************************/
static BOOL extrapolateXI(INT32 step)
{
    static enum
    {
        REQUEST_NEIGHBORS_XI,
        RECEIVE_NEIGHBORS_XI,
        EXTRAPOLATE_XI
    } extrapolateXIState = REQUEST_NEIGHBORS_XI;

    switch (extrapolateXIState)
    {
        case REQUEST_NEIGHBORS_XI:
            if (northern)
                getNeighborsValuesUDP(XI, step, 2, SOUTH, NORTH);
            else if (eastern)
                getNeighborsValuesUDP(XI, step, 2, WEST, EAST);
            else if (southern)
                getNeighborsValuesUDP(XI, step, 2, NORTH, SOUTH);
            else if (western)
                getNeighborsValuesUDP(XI, step, 2, EAST, WEST);

            extrapolateXIState = RECEIVE_NEIGHBORS_XI;
            break;

        case RECEIVE_NEIGHBORS_XI:
            if (northern)
            {
                if (!neighborsValuesUDPFinished(2, SOUTH, NORTH))
                    break;
            }
            else if (eastern)
            {
                if (!neighborsValuesUDPFinished(2, WEST, EAST))
                    break;
            }
            else if (southern)
            {
                if (!neighborsValuesUDPFinished(2, NORTH, SOUTH))
                    break;
            }
            else if (western)
            {
                if (!neighborsValuesUDPFinished(2, EAST, WEST))
                    break;
            }

            extrapolateXIState = EXTRAPOLATE_XI;
            // Do not break here

        case EXTRAPOLATE_XI:
        {
            float xiNew;
            
            if (northern)
                xiNew = 2*(getNeighborValue(SOUTH)) - getNeighborValue(NORTH);
            else if (eastern)
                xiNew = 2*(getNeighborValue(WEST)) - getNeighborValue(EAST);
            else if (southern)
                xiNew = 2*(getNeighborValue(NORTH)) - getNeighborValue(SOUTH);
            else if (western)
                xiNew = 2*(getNeighborValue(EAST)) - getNeighborValue(WEST);

            setValue(XI, step, xiNew);

            extrapolateXIState = REQUEST_NEIGHBORS_XI;
            return TRUE;
        }
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	static BOOL calculateDXIDT(INT32 step)

  Description:
	This function is used for calculating the value of DXIDT.
        It queries its neighbors for Z and ETA values and then does the calculations.

  Precondition:
        node is initialized

  Parameters:
        step - current main iteration step

  Returns:
        TRUE if the calculation process finished
        FALSE otherwise (in progress)
******************************************************************************/
static BOOL calculateDXIDT(INT32 step)
{
    static float dzdx, dzdy, detadx, detady;

    static enum
    {
        REQUEST_NEIGHBORS_Z,
        RECEIVE_NEIGHBORS_Z,
        REQUEST_NEIGHBORS_ETA,
        RECEIVE_NEIGHBORS_ETA,
        CALCULATE_DXIDT
    } calculateDXIDTState = REQUEST_NEIGHBORS_Z;

    switch(calculateDXIDTState)
    {
        case REQUEST_NEIGHBORS_Z:
            getNeighborsValuesUDP(Z, step, NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST);

            calculateDXIDTState = RECEIVE_NEIGHBORS_Z;
            break;

        case RECEIVE_NEIGHBORS_Z:
            if (!neighborsValuesUDPFinished(NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST))
                break;

            /* dz/dx(i,j) = (z(i+1,j)-z(i-1,j))/(2*DS) */
            dzdx = (getNeighborValue(EAST) - getNeighborValue(WEST)) / (2*DS);
            /* dz/dy(i,j) = (z(i,j+1)-z(i,j-1))/(2*DS) */
            dzdy = (getNeighborValue(NORTH) - getNeighborValue(SOUTH)) / (2*DS);

            calculateDXIDTState = REQUEST_NEIGHBORS_ETA;
            // Do not break here

        case REQUEST_NEIGHBORS_ETA:
            getNeighborsValuesUDP(ETA, step, NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST);

            calculateDXIDTState = RECEIVE_NEIGHBORS_ETA;
            break;

        case RECEIVE_NEIGHBORS_ETA:
            if (!neighborsValuesUDPFinished(NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST))
                break;

            /* deta/dx(i,j) = (eta(i+1,j)-eta(i-1,j))/(2*DS) */
            detadx = (getNeighborValue(EAST) - getNeighborValue(WEST)) / (2*DS);
            /* deta/dy(i,j) = (eta(i,j+1)-eta(i,j-1))/(2*DS) */
            detady = (getNeighborValue(NORTH) - getNeighborValue(SOUTH)) / (2*DS);

            calculateDXIDTState = CALCULATE_DXIDT;
            // Do not break here

        case CALCULATE_DXIDT:
            /* dxi/dt(i,j) = Jacobi(i,j) = (deta/dx * dz/dy - deta/dy * dz/dx) */
            setValue(DXIDT, step, detadx*dzdy - detady*dzdx);

            calculateDXIDTState = REQUEST_NEIGHBORS_Z;
            return TRUE;
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	static BOOL solvePoissonEquation(INT32 step)

  Description:
	This function is used for solving the Poisson equation.
        It queries its neighbors for DZDT values and then does the calculations.

  Precondition:
        the value of DXIDT is available

  Parameters:
        step - current main iteration step

  Returns:
        TRUE if the calculation process finished
        FALSE otherwise (in progress)
******************************************************************************/
static BOOL solvePoissonEquation(INT32 step)
{
    static INT32 it_step = 0;

    static enum
    {
        REQUEST_NEIGHBORS_DZDT,
        RECEIVE_NEIGHBORS_DZDT,
        APPROXIMATE_DZDT
    } poissonEquationState = REQUEST_NEIGHBORS_DZDT;

    SevenSegmentDisplay(it_step);

    switch (poissonEquationState)
    {
        case REQUEST_NEIGHBORS_DZDT:
            getNeighborsValuesUDP(DZDT, it_step, NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST);

            poissonEquationState = RECEIVE_NEIGHBORS_DZDT;
            break;

        case RECEIVE_NEIGHBORS_DZDT:
            if (!neighborsValuesUDPFinished(NUM_NEIGHBORS, NORTH, EAST, SOUTH, WEST))
                break;

            poissonEquationState = APPROXIMATE_DZDT;
            // Do not break here

        case APPROXIMATE_DZDT:
        {
            /* dz/dt(i,j) = (1/4)*(dz/dt(i+1,j) + dz/dt(i-1,j) + dz/dt(i,j+1) + dz/dt(i,j-1) - Jacobi(i,j)*(DS^2))) */
            float sum = 0;
            Neighbors n;

            for (n=0; n<NUM_NEIGHBORS; n++)
                sum += getNeighborValue(n);

            setValue(DZDT, ++it_step, (sum - (getValue(DXIDT, step)*DS)*DS) / 4);

            poissonEquationState = REQUEST_NEIGHBORS_DZDT;

            if (it_step == NUM_ITERATIONS)
            {
                it_step = 0;
                return TRUE;
            }
            break;
        }
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	static BOOL extrapolateDXIDT(INT32 step)

  Description:
	This function is used for extrapolating the value of DXIDT.
        It queries its neighbors for DXIDT values and then does the calculations.

  Precondition:
        node is initialized

  Parameters:
        step - current main iteration step

  Returns:
        TRUE if the extrapolation process finished
        FALSE otherwise (in progress)
******************************************************************************/
static BOOL extrapolateDXIDT(INT32 step)
{
    static enum
    {
        REQUEST_NEIGHBORS_DXIDT,
        RECEIVE_NEIGHBORS_DXIDT,
        EXTRAPOLATE_DXIDT
    } extrapolateDXIDTState = REQUEST_NEIGHBORS_DXIDT;

    switch (extrapolateDXIDTState)
    {
        case REQUEST_NEIGHBORS_DXIDT:
            if (northern)
                getNeighborsValuesUDP(DXIDT, step, 2, SOUTH, NORTH);
            else if (eastern)
                getNeighborsValuesUDP(DXIDT, step, 2, WEST, EAST);
            else if (southern)
                getNeighborsValuesUDP(DXIDT, step, 2, NORTH, SOUTH);
            else if (western)
                getNeighborsValuesUDP(DXIDT, step, 2, EAST, WEST);

            extrapolateDXIDTState = RECEIVE_NEIGHBORS_DXIDT;
            break;

        case RECEIVE_NEIGHBORS_DXIDT:
            if (northern && !neighborsValuesUDPFinished(2, SOUTH, NORTH))
                break;
            else if (eastern && !neighborsValuesUDPFinished(2, WEST, EAST))
                break;
            else if (southern && !neighborsValuesUDPFinished(2, NORTH, SOUTH))
                break;
            else if (western && !neighborsValuesUDPFinished(2, EAST, WEST))
                break;

            extrapolateDXIDTState = EXTRAPOLATE_DXIDT;
            // Do not break here

        case EXTRAPOLATE_DXIDT:
        {
            float dxidtNew;

            if (northern)
                dxidtNew = 2*(getNeighborValue(SOUTH)) - getNeighborValue(NORTH);
            else if (eastern)
                dxidtNew = 2*(getNeighborValue(WEST)) - getNeighborValue(EAST);
            else if (southern)
                dxidtNew = 2*(getNeighborValue(NORTH)) - getNeighborValue(SOUTH);
            else if (western)
                dxidtNew = 2*(getNeighborValue(EAST)) - getNeighborValue(WEST);

            setValue(DXIDT, step, dxidtNew);

            extrapolateDXIDTState = REQUEST_NEIGHBORS_DXIDT;
            return TRUE;
        }
    }
    return FALSE;
}



/*****************************************************************************
  Function:
	float getValue(DataTypes dt, INT32 step)

  Description:
	This function returns the value of a given data field.

  Precondition:
        None

  Parameters:
        dt - the type of data value
        step - the step of the requested data value

  Returns:
        the value of the requested data field
******************************************************************************/
float getValue(DataTypes dt, INT32 step)
{
    /* If the requested data is unavailable, return NaN */
    switch (dt)
    {
        case Z:
            if (step > z.step)
                return NAN;
            return z.dataArray[step];
        case DZDT:
            if ( (step > dzdt.step) || ( (step==0) && dzdt.denyNextStepRequests ) )
                return NAN;
            return dzdt.dataArray[step];
        case XI:
            if (step > xi.step)
                return NAN;
            return xi.dataArray[step];
        case DXIDT:
            if (step > dxidt.step)
                return NAN;
            return dxidt.dataArray[step];
        case ETA:
            if (step > eta.step)
                return NAN;
            return eta.dataArray[step];
        default:
            return NAN;
    }
}


/*****************************************************************************
  Function:
	float setValue(DataTypes dt, INT32 step, float value)

  Description:
	This function sets the value of a data field.

  Precondition:
        None

  Parameters:
        dt - the type of data value
        step - the step of the requested data value
        value - the new value of the data field

  Returns:
        None
******************************************************************************/
static void setValue(DataTypes dt, INT32 step, float value)
{
    switch (dt)
    {
        case Z:
            z.dataArray[step] = value;
            z.step = step;
            break;
        case DZDT:
            dzdt.dataArray[step] = value;
            dzdt.step = step;
            break;
        case XI:
            xi.dataArray[step] = value;
            xi.step = step;
            break;
        case DXIDT:
            dxidt.dataArray[step] = value;
            dxidt.step = step;
            break;
        case ETA:
            eta.dataArray[step] = value;
            eta.step = step;
            break;
        default:
            break;
    }
}



/*****************************************************************************
  Function:
	static void getNeighborsValuesUDP(DataTypes dt, INT32 step, int num_neighbors, ...)

  Description:
	This function is used for querying neighbors for their current values.
        It is only used to start the UDP clients.

  Precondition:
        None

  Parameters:
        dt - the type of data value
        step - the step of the requested data value
        num_neighbors - the number of the neighbors to query

  Returns:
        None
******************************************************************************/
static void getNeighborsValuesUDP(DataTypes dt, INT32 step, int num_neighbors, ...)
{
    va_list args;
    Neighbors n;
    int i;

    va_start(args, num_neighbors);
    for (i=0; i<num_neighbors; i++)
    {
        n = va_arg(args, Neighbors);
        getNeighborValueUDP(n, dt, step);
    }
    va_end(args);
}



/*****************************************************************************
  Function:
	static BOOL neighborsValuesUDPFinished(int num_neighbors, ...)

  Description:
	This function is used to check if the UDP clients have finished.

  Precondition:
        None

  Parameters:
        num_neighbors - the number of the queried neighbors

  Returns:
        TRUE if the clients have finished
        FALSE otherwise
******************************************************************************/
static BOOL neighborsValuesUDPFinished(int num_neighbors, ...)
{
    va_list args;
    int i;

    va_start(args, num_neighbors);
    for (i=0; i<num_neighbors; i++)
    {
        if (!nodeUDPClientFinished(va_arg(args, Neighbors)))
        {
            va_end(args);
            return FALSE;
        }
    }
    va_end(args);
    return TRUE;
}
