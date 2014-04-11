#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-18F67J60.mk)" "nbproject/Makefile-local-18F67J60.mk"
include nbproject/Makefile-local-18F67J60.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=18F67J60
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ENIAC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ENIAC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Node.o ${OBJECTDIR}/NodeTCPClient0.o ${OBJECTDIR}/NodeTCPClient1.o ${OBJECTDIR}/NodeUDPClient.o ${OBJECTDIR}/NodeUDPServer.o ${OBJECTDIR}/MPL3115A2.o ${OBJECTDIR}/MCP9808.o ${OBJECTDIR}/I2CHelpers.o ${OBJECTDIR}/HIH-5031.o ${OBJECTDIR}/Sensors.o "${OBJECTDIR}/Microchip/TCPIP Stack/Announce.o" "${OBJECTDIR}/Microchip/TCPIP Stack/ARP.o" "${OBJECTDIR}/Microchip/TCPIP Stack/BerkeleyAPI.o" "${OBJECTDIR}/Microchip/TCPIP Stack/Delay.o" "${OBJECTDIR}/Microchip/TCPIP Stack/DHCP.o" "${OBJECTDIR}/Microchip/TCPIP Stack/ETH97J60.o" "${OBJECTDIR}/Microchip/TCPIP Stack/Helpers.o" "${OBJECTDIR}/Microchip/TCPIP Stack/ICMP.o" "${OBJECTDIR}/Microchip/TCPIP Stack/IP.o" "${OBJECTDIR}/Microchip/TCPIP Stack/Reboot.o" "${OBJECTDIR}/Microchip/TCPIP Stack/StackTsk.o" "${OBJECTDIR}/Microchip/TCPIP Stack/TCP.o" "${OBJECTDIR}/Microchip/TCPIP Stack/Tick.o" "${OBJECTDIR}/Microchip/TCPIP Stack/UDP.o" ${OBJECTDIR}/Main.o ${OBJECTDIR}/7segment.o ${OBJECTDIR}/Setup.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Node.o.d ${OBJECTDIR}/NodeTCPClient0.o.d ${OBJECTDIR}/NodeTCPClient1.o.d ${OBJECTDIR}/NodeUDPClient.o.d ${OBJECTDIR}/NodeUDPServer.o.d ${OBJECTDIR}/MPL3115A2.o.d ${OBJECTDIR}/MCP9808.o.d ${OBJECTDIR}/I2CHelpers.o.d ${OBJECTDIR}/HIH-5031.o.d ${OBJECTDIR}/Sensors.o.d "${OBJECTDIR}/Microchip/TCPIP Stack/Announce.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/ARP.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/BerkeleyAPI.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/Delay.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/DHCP.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/ETH97J60.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/Helpers.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/ICMP.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/IP.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/Reboot.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/StackTsk.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/TCP.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/Tick.o.d" "${OBJECTDIR}/Microchip/TCPIP Stack/UDP.o.d" ${OBJECTDIR}/Main.o.d ${OBJECTDIR}/7segment.o.d ${OBJECTDIR}/Setup.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Node.o ${OBJECTDIR}/NodeTCPClient0.o ${OBJECTDIR}/NodeTCPClient1.o ${OBJECTDIR}/NodeUDPClient.o ${OBJECTDIR}/NodeUDPServer.o ${OBJECTDIR}/MPL3115A2.o ${OBJECTDIR}/MCP9808.o ${OBJECTDIR}/I2CHelpers.o ${OBJECTDIR}/HIH-5031.o ${OBJECTDIR}/Sensors.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/Announce.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/ARP.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/BerkeleyAPI.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/Delay.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/DHCP.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/ETH97J60.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/Helpers.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/ICMP.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/IP.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/Reboot.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/StackTsk.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/TCP.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/Tick.o ${OBJECTDIR}/Microchip/TCPIP\ Stack/UDP.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/7segment.o ${OBJECTDIR}/Setup.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-18F67J60.mk dist/${CND_CONF}/${IMAGE_TYPE}/ENIAC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F67J60
MP_PROCESSOR_OPTION_LD=18f67j60
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Node.o: Node.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Node.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Node.o   Node.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Node.o 
	
${OBJECTDIR}/NodeTCPClient0.o: NodeTCPClient0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeTCPClient0.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeTCPClient0.o   NodeTCPClient0.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeTCPClient0.o 
	
${OBJECTDIR}/NodeTCPClient1.o: NodeTCPClient1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeTCPClient1.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeTCPClient1.o   NodeTCPClient1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeTCPClient1.o 
	
${OBJECTDIR}/NodeUDPClient.o: NodeUDPClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeUDPClient.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeUDPClient.o   NodeUDPClient.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeUDPClient.o 
	
${OBJECTDIR}/NodeUDPServer.o: NodeUDPServer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeUDPServer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeUDPServer.o   NodeUDPServer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeUDPServer.o 
	
${OBJECTDIR}/MPL3115A2.o: MPL3115A2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/MPL3115A2.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/MPL3115A2.o   MPL3115A2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/MPL3115A2.o 
	
${OBJECTDIR}/MCP9808.o: MCP9808.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/MCP9808.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/MCP9808.o   MCP9808.c 
	@${DEP_GEN} -d ${OBJECTDIR}/MCP9808.o 
	
${OBJECTDIR}/I2CHelpers.o: I2CHelpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/I2CHelpers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/I2CHelpers.o   I2CHelpers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/I2CHelpers.o 
	
${OBJECTDIR}/HIH-5031.o: HIH-5031.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HIH-5031.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/HIH-5031.o   HIH-5031.c 
	@${DEP_GEN} -d ${OBJECTDIR}/HIH-5031.o 
	
${OBJECTDIR}/Sensors.o: Sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sensors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Sensors.o   Sensors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Sensors.o 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Announce.o: Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Announce.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Announce.o"   "Microchip/TCPIP Stack/Announce.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Announce.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/ARP.o: Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/ARP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/ARP.o"   "Microchip/TCPIP Stack/ARP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/ARP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/BerkeleyAPI.o: Microchip/TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/BerkeleyAPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/BerkeleyAPI.o"   "Microchip/TCPIP Stack/BerkeleyAPI.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/BerkeleyAPI.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Delay.o: Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Delay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Delay.o"   "Microchip/TCPIP Stack/Delay.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Delay.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/DHCP.o: Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/DHCP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/DHCP.o"   "Microchip/TCPIP Stack/DHCP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/DHCP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/ETH97J60.o: Microchip/TCPIP\ Stack/ETH97J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/ETH97J60.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/ETH97J60.o"   "Microchip/TCPIP Stack/ETH97J60.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/ETH97J60.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Helpers.o: Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Helpers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Helpers.o"   "Microchip/TCPIP Stack/Helpers.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Helpers.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/ICMP.o: Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/ICMP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/ICMP.o"   "Microchip/TCPIP Stack/ICMP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/ICMP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/IP.o: Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/IP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/IP.o"   "Microchip/TCPIP Stack/IP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/IP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Reboot.o: Microchip/TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Reboot.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Reboot.o"   "Microchip/TCPIP Stack/Reboot.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Reboot.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/StackTsk.o: Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/StackTsk.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/StackTsk.o"   "Microchip/TCPIP Stack/StackTsk.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/StackTsk.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/TCP.o: Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/TCP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/TCP.o"   "Microchip/TCPIP Stack/TCP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/TCP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Tick.o: Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Tick.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Tick.o"   "Microchip/TCPIP Stack/Tick.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Tick.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/UDP.o: Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/UDP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/UDP.o"   "Microchip/TCPIP Stack/UDP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/UDP.o" 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Main.o   Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Main.o 
	
${OBJECTDIR}/7segment.o: 7segment.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/7segment.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/7segment.o   7segment.c 
	@${DEP_GEN} -d ${OBJECTDIR}/7segment.o 
	
${OBJECTDIR}/Setup.o: Setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Setup.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Setup.o   Setup.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Setup.o 
	
else
${OBJECTDIR}/Node.o: Node.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Node.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Node.o   Node.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Node.o 
	
${OBJECTDIR}/NodeTCPClient0.o: NodeTCPClient0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeTCPClient0.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeTCPClient0.o   NodeTCPClient0.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeTCPClient0.o 
	
${OBJECTDIR}/NodeTCPClient1.o: NodeTCPClient1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeTCPClient1.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeTCPClient1.o   NodeTCPClient1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeTCPClient1.o 
	
${OBJECTDIR}/NodeUDPClient.o: NodeUDPClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeUDPClient.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeUDPClient.o   NodeUDPClient.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeUDPClient.o 
	
${OBJECTDIR}/NodeUDPServer.o: NodeUDPServer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NodeUDPServer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NodeUDPServer.o   NodeUDPServer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NodeUDPServer.o 
	
${OBJECTDIR}/MPL3115A2.o: MPL3115A2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/MPL3115A2.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/MPL3115A2.o   MPL3115A2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/MPL3115A2.o 
	
${OBJECTDIR}/MCP9808.o: MCP9808.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/MCP9808.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/MCP9808.o   MCP9808.c 
	@${DEP_GEN} -d ${OBJECTDIR}/MCP9808.o 
	
${OBJECTDIR}/I2CHelpers.o: I2CHelpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/I2CHelpers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/I2CHelpers.o   I2CHelpers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/I2CHelpers.o 
	
${OBJECTDIR}/HIH-5031.o: HIH-5031.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HIH-5031.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/HIH-5031.o   HIH-5031.c 
	@${DEP_GEN} -d ${OBJECTDIR}/HIH-5031.o 
	
${OBJECTDIR}/Sensors.o: Sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sensors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Sensors.o   Sensors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Sensors.o 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Announce.o: Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Announce.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Announce.o"   "Microchip/TCPIP Stack/Announce.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Announce.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/ARP.o: Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/ARP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/ARP.o"   "Microchip/TCPIP Stack/ARP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/ARP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/BerkeleyAPI.o: Microchip/TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/BerkeleyAPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/BerkeleyAPI.o"   "Microchip/TCPIP Stack/BerkeleyAPI.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/BerkeleyAPI.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Delay.o: Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Delay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Delay.o"   "Microchip/TCPIP Stack/Delay.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Delay.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/DHCP.o: Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/DHCP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/DHCP.o"   "Microchip/TCPIP Stack/DHCP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/DHCP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/ETH97J60.o: Microchip/TCPIP\ Stack/ETH97J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/ETH97J60.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/ETH97J60.o"   "Microchip/TCPIP Stack/ETH97J60.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/ETH97J60.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Helpers.o: Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Helpers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Helpers.o"   "Microchip/TCPIP Stack/Helpers.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Helpers.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/ICMP.o: Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/ICMP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/ICMP.o"   "Microchip/TCPIP Stack/ICMP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/ICMP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/IP.o: Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/IP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/IP.o"   "Microchip/TCPIP Stack/IP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/IP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Reboot.o: Microchip/TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Reboot.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Reboot.o"   "Microchip/TCPIP Stack/Reboot.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Reboot.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/StackTsk.o: Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/StackTsk.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/StackTsk.o"   "Microchip/TCPIP Stack/StackTsk.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/StackTsk.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/TCP.o: Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/TCP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/TCP.o"   "Microchip/TCPIP Stack/TCP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/TCP.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/Tick.o: Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/Tick.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/Tick.o"   "Microchip/TCPIP Stack/Tick.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/Tick.o" 
	
${OBJECTDIR}/Microchip/TCPIP\ Stack/UDP.o: Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/Microchip/TCPIP\ Stack/UDP.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo "${OBJECTDIR}/Microchip/TCPIP Stack/UDP.o"   "Microchip/TCPIP Stack/UDP.c" 
	@${DEP_GEN} -d "${OBJECTDIR}/Microchip/TCPIP Stack/UDP.o" 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Main.o   Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Main.o 
	
${OBJECTDIR}/7segment.o: 7segment.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/7segment.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/7segment.o   7segment.c 
	@${DEP_GEN} -d ${OBJECTDIR}/7segment.o 
	
${OBJECTDIR}/Setup.o: Setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Setup.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -DCFG_INCLUDE_WSN_BOARD -I"." -I"./Configs" -I"./Microchip/Include" -I"./Microchip/Include/TCPIP Stack" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Setup.o   Setup.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Setup.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ENIAC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "Linker\18f67j60_eniac.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l".."  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/ENIAC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/ENIAC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "Linker\18f67j60_eniac.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l".."  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/ENIAC.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/18F67J60
	${RM} -r dist/18F67J60

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
