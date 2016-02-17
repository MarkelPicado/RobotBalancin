#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Acelerometro_v1_1.c ../CAD_v1_1.c ../Conversiones_L.c ../Giroscopo_v1_1.c ../IO.c ../Inic_Timer_7.c ../LCD.c ../PWM.c ../PidyKalman.c ../RS232_DMA_24H.c ../i2c_Func_DSE_AM.c ../main_balancin_v1_1.c ../config.c ../config_fuse.c ../init.c ../peripheral.c ../peripheral_string.c ../timer.c ../uart_L_24H.c ../lcd1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o ${OBJECTDIR}/_ext/1472/CAD_v1_1.o ${OBJECTDIR}/_ext/1472/Conversiones_L.o ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o ${OBJECTDIR}/_ext/1472/IO.o ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o ${OBJECTDIR}/_ext/1472/LCD.o ${OBJECTDIR}/_ext/1472/PWM.o ${OBJECTDIR}/_ext/1472/PidyKalman.o ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o ${OBJECTDIR}/_ext/1472/config.o ${OBJECTDIR}/_ext/1472/config_fuse.o ${OBJECTDIR}/_ext/1472/init.o ${OBJECTDIR}/_ext/1472/peripheral.o ${OBJECTDIR}/_ext/1472/peripheral_string.o ${OBJECTDIR}/_ext/1472/timer.o ${OBJECTDIR}/_ext/1472/uart_L_24H.o ${OBJECTDIR}/_ext/1472/lcd1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o.d ${OBJECTDIR}/_ext/1472/CAD_v1_1.o.d ${OBJECTDIR}/_ext/1472/Conversiones_L.o.d ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o.d ${OBJECTDIR}/_ext/1472/IO.o.d ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o.d ${OBJECTDIR}/_ext/1472/LCD.o.d ${OBJECTDIR}/_ext/1472/PWM.o.d ${OBJECTDIR}/_ext/1472/PidyKalman.o.d ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o.d ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o.d ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o.d ${OBJECTDIR}/_ext/1472/config.o.d ${OBJECTDIR}/_ext/1472/config_fuse.o.d ${OBJECTDIR}/_ext/1472/init.o.d ${OBJECTDIR}/_ext/1472/peripheral.o.d ${OBJECTDIR}/_ext/1472/peripheral_string.o.d ${OBJECTDIR}/_ext/1472/timer.o.d ${OBJECTDIR}/_ext/1472/uart_L_24H.o.d ${OBJECTDIR}/_ext/1472/lcd1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o ${OBJECTDIR}/_ext/1472/CAD_v1_1.o ${OBJECTDIR}/_ext/1472/Conversiones_L.o ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o ${OBJECTDIR}/_ext/1472/IO.o ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o ${OBJECTDIR}/_ext/1472/LCD.o ${OBJECTDIR}/_ext/1472/PWM.o ${OBJECTDIR}/_ext/1472/PidyKalman.o ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o ${OBJECTDIR}/_ext/1472/config.o ${OBJECTDIR}/_ext/1472/config_fuse.o ${OBJECTDIR}/_ext/1472/init.o ${OBJECTDIR}/_ext/1472/peripheral.o ${OBJECTDIR}/_ext/1472/peripheral_string.o ${OBJECTDIR}/_ext/1472/timer.o ${OBJECTDIR}/_ext/1472/uart_L_24H.o ${OBJECTDIR}/_ext/1472/lcd1.o

# Source Files
SOURCEFILES=../Acelerometro_v1_1.c ../CAD_v1_1.c ../Conversiones_L.c ../Giroscopo_v1_1.c ../IO.c ../Inic_Timer_7.c ../LCD.c ../PWM.c ../PidyKalman.c ../RS232_DMA_24H.c ../i2c_Func_DSE_AM.c ../main_balancin_v1_1.c ../config.c ../config_fuse.c ../init.c ../peripheral.c ../peripheral_string.c ../timer.c ../uart_L_24H.c ../lcd1.c


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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24HJ256GP610A
MP_LINKER_FILE_OPTION=,--script=p24HJ256GP610A.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o: ../Acelerometro_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Acelerometro_v1_1.c  -o ${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/CAD_v1_1.o: ../CAD_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CAD_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CAD_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CAD_v1_1.c  -o ${OBJECTDIR}/_ext/1472/CAD_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/CAD_v1_1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CAD_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Conversiones_L.o: ../Conversiones_L.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Conversiones_L.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Conversiones_L.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Conversiones_L.c  -o ${OBJECTDIR}/_ext/1472/Conversiones_L.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Conversiones_L.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Conversiones_L.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o: ../Giroscopo_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Giroscopo_v1_1.c  -o ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/IO.o: ../IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/IO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../IO.c  -o ${OBJECTDIR}/_ext/1472/IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/IO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/IO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Inic_Timer_7.o: ../Inic_Timer_7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Inic_Timer_7.c  -o ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Inic_Timer_7.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Inic_Timer_7.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/LCD.o: ../LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../LCD.c  -o ${OBJECTDIR}/_ext/1472/LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/LCD.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/PWM.o: ../PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../PWM.c  -o ${OBJECTDIR}/_ext/1472/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/PWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/PidyKalman.o: ../PidyKalman.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PidyKalman.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PidyKalman.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../PidyKalman.c  -o ${OBJECTDIR}/_ext/1472/PidyKalman.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/PidyKalman.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PidyKalman.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o: ../RS232_DMA_24H.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RS232_DMA_24H.c  -o ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o: ../i2c_Func_DSE_AM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../i2c_Func_DSE_AM.c  -o ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o: ../main_balancin_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main_balancin_v1_1.c  -o ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../config.c  -o ${OBJECTDIR}/_ext/1472/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/config_fuse.o: ../config_fuse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config_fuse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config_fuse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../config_fuse.c  -o ${OBJECTDIR}/_ext/1472/config_fuse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/config_fuse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/config_fuse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/init.o: ../init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../init.c  -o ${OBJECTDIR}/_ext/1472/init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/peripheral.o: ../peripheral.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../peripheral.c  -o ${OBJECTDIR}/_ext/1472/peripheral.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/peripheral.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/peripheral.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/peripheral_string.o: ../peripheral_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../peripheral_string.c  -o ${OBJECTDIR}/_ext/1472/peripheral_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/peripheral_string.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/peripheral_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/timer.o: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../timer.c  -o ${OBJECTDIR}/_ext/1472/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/uart_L_24H.o: ../uart_L_24H.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart_L_24H.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart_L_24H.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../uart_L_24H.c  -o ${OBJECTDIR}/_ext/1472/uart_L_24H.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/uart_L_24H.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/uart_L_24H.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/lcd1.o: ../lcd1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/lcd1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/lcd1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lcd1.c  -o ${OBJECTDIR}/_ext/1472/lcd1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/lcd1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/lcd1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o: ../Acelerometro_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Acelerometro_v1_1.c  -o ${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Acelerometro_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/CAD_v1_1.o: ../CAD_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CAD_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CAD_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CAD_v1_1.c  -o ${OBJECTDIR}/_ext/1472/CAD_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/CAD_v1_1.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CAD_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Conversiones_L.o: ../Conversiones_L.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Conversiones_L.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Conversiones_L.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Conversiones_L.c  -o ${OBJECTDIR}/_ext/1472/Conversiones_L.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Conversiones_L.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Conversiones_L.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o: ../Giroscopo_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Giroscopo_v1_1.c  -o ${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Giroscopo_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/IO.o: ../IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/IO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../IO.c  -o ${OBJECTDIR}/_ext/1472/IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/IO.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/IO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Inic_Timer_7.o: ../Inic_Timer_7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Inic_Timer_7.c  -o ${OBJECTDIR}/_ext/1472/Inic_Timer_7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Inic_Timer_7.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Inic_Timer_7.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/LCD.o: ../LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../LCD.c  -o ${OBJECTDIR}/_ext/1472/LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/LCD.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/PWM.o: ../PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../PWM.c  -o ${OBJECTDIR}/_ext/1472/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/PWM.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/PidyKalman.o: ../PidyKalman.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PidyKalman.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PidyKalman.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../PidyKalman.c  -o ${OBJECTDIR}/_ext/1472/PidyKalman.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/PidyKalman.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PidyKalman.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o: ../RS232_DMA_24H.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RS232_DMA_24H.c  -o ${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RS232_DMA_24H.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o: ../i2c_Func_DSE_AM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../i2c_Func_DSE_AM.c  -o ${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_Func_DSE_AM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o: ../main_balancin_v1_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main_balancin_v1_1.c  -o ${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main_balancin_v1_1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../config.c  -o ${OBJECTDIR}/_ext/1472/config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/config_fuse.o: ../config_fuse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config_fuse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config_fuse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../config_fuse.c  -o ${OBJECTDIR}/_ext/1472/config_fuse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/config_fuse.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/config_fuse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/init.o: ../init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../init.c  -o ${OBJECTDIR}/_ext/1472/init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/peripheral.o: ../peripheral.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../peripheral.c  -o ${OBJECTDIR}/_ext/1472/peripheral.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/peripheral.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/peripheral.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/peripheral_string.o: ../peripheral_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/peripheral_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../peripheral_string.c  -o ${OBJECTDIR}/_ext/1472/peripheral_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/peripheral_string.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/peripheral_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/timer.o: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../timer.c  -o ${OBJECTDIR}/_ext/1472/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/timer.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/uart_L_24H.o: ../uart_L_24H.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart_L_24H.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart_L_24H.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../uart_L_24H.c  -o ${OBJECTDIR}/_ext/1472/uart_L_24H.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/uart_L_24H.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/uart_L_24H.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/lcd1.o: ../lcd1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/lcd1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/lcd1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lcd1.c  -o ${OBJECTDIR}/_ext/1472/lcd1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/lcd1.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/lcd1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pdi_am_2.x.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
