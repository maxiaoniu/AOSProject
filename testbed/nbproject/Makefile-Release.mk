#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CMPWEpoll.o \
	${OBJECTDIR}/CMPWListenHandle.o \
	${OBJECTDIR}/CMPWNode.o \
	${OBJECTDIR}/CMPWReactor.o \
	${OBJECTDIR}/CMPWSocket.o \
	${OBJECTDIR}/CMPWSocketIOHandle.o \
	${OBJECTDIR}/CMPWTimer.o \
	${OBJECTDIR}/CMPWTimerHandle.o \
	${OBJECTDIR}/CMPWUtils.o \
	${OBJECTDIR}/TestbedOption.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lrt
CXXFLAGS=-lrt

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbed

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbed: -lrt

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbed: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbed ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/CMPWEpoll.o: CMPWEpoll.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWEpoll.o CMPWEpoll.cpp

${OBJECTDIR}/CMPWListenHandle.o: CMPWListenHandle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWListenHandle.o CMPWListenHandle.cpp

${OBJECTDIR}/CMPWNode.o: CMPWNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWNode.o CMPWNode.cpp

${OBJECTDIR}/CMPWReactor.o: CMPWReactor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWReactor.o CMPWReactor.cpp

${OBJECTDIR}/CMPWSocket.o: CMPWSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWSocket.o CMPWSocket.cpp

${OBJECTDIR}/CMPWSocketIOHandle.o: CMPWSocketIOHandle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWSocketIOHandle.o CMPWSocketIOHandle.cpp

${OBJECTDIR}/CMPWTimer.o: CMPWTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWTimer.o CMPWTimer.cpp

${OBJECTDIR}/CMPWTimerHandle.o: CMPWTimerHandle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWTimerHandle.o CMPWTimerHandle.cpp

${OBJECTDIR}/CMPWUtils.o: CMPWUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMPWUtils.o CMPWUtils.cpp

${OBJECTDIR}/TestbedOption.o: TestbedOption.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestbedOption.o TestbedOption.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbed

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
