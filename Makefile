# Project root path from (to project)
Prdir:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
Headers=${Prdir}/Headers
Sources=${Prdir}/Sources

# Setting of the general compiled grammer
## The Compiler, library, level of the compiler optimization, detected information, wall and message
Cmp=gcc
Stdlib=-std=c99
Cmpopt=-O3
Detinfo=-g3
Wall=-Wall
Fsg=-fmessage-length=0 -pthread
#OpenSSL3=-I../../../include
OpenSSL3=

## Project execution's name
PjN:= $(word $(words $(subst /, ,${Prdir})), $(subst /, ,${Prdir}))

# Make's Processes
.Suffixs: .c .h

.Phony: all
all: ${Prdir}/${PjN}

.Phony: build
build: ${Prdir}/${PjN}/build

.Phony: clean
clean:
	clear
	rm -rf ${Sources}/*.o
	rm -rf ${Sources}/*/*.o
	rm -rf ${Prdir}/${PjN}
	rm -rf ${Prdir}/*.o

.Phony: run
run:
	${Prdir}/${PjN}

##================================================================
# Build libraries
${Prdir}/${PjN}/build : 	${Sources}/Encryptions/EncodeDispatcher.o \
							${Sources}/Encryptions/Encode.o \
							${Sources}/Encryptions/AES_256_GCM.o \
							${Sources}/FileGenerations/FileGeneration.o

# Create a module
${Prdir}/${PjN}: 	${Prdir}/Main.o \
					${Sources}/Encryptions/EncodeDispatcher.o \
					${Sources}/Encryptions/Encode.o \
					${Sources}/Encryptions/AES_256_GCM.o \
					${Sources}/FileGenerations/FileGeneration.o

	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Fsg} -o ${Prdir}/${PjN} ${Prdir}/Main.o \
	${Sources}/Encryptions/EncodeDispatcher.o \
	${Sources}/Encryptions/Encode.o \
	${Sources}/Encryptions/AES_256_GCM.o \
	${Sources}/FileGenerations/FileGeneration.o \
	-lssl -lcrypto

# Main
${Prdir}/Main.o:	${Headers}/Header.h ${Headers}/Encryptions/EncodeDispatcher.h ${Prdir}/Main.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Prdir}/Main.c -c ${Fsg} -o ${Prdir}/Main.o

# EncodeDispatcher
${Sources}/Encryptions/EncodeDispatcher.o:	${Headers}/Encryptions/EncodeDispatcher.h ${Headers}/Encryptions/Encode.h ${Headers}/Encryptions/AES_256_GCM.h ${Sources}/Encryptions/EncodeDispatcher.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/Encryptions/EncodeDispatcher.c -c ${Fsg} -o ${Sources}/Encryptions/EncodeDispatcher.o ${OpenSSL3}

# Encode
${Sources}/Encryptions/Encode.o:	${Headers}/Encryptions/Encode.h ${Headers}/Encryptions/Encode.h ${Headers}/Encryptions/AES_256_GCM.h ${Sources}/Encryptions/Encode.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/Encryptions/Encode.c -c ${Fsg} -o ${Sources}/Encryptions/Encode.o ${OpenSSL3}

# AES_256_GCM
${Sources}/Encryptions/AES_256_GCM.o:	${Headers}/FileGenerations/FileGeneration.h ${Headers}/Encryptions/AES_256_GCM.h ${Headers}/Encryptions/Encode.h ${Sources}/Encryptions/AES_256_GCM.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/Encryptions/AES_256_GCM.c -c ${Fsg} -o ${Sources}/Encryptions/AES_256_GCM.o ${OpenSSL3}

# FileGeneration
${Sources}/FileGenerations/FileGeneration.o:	${Headers}/FileGenerations/FileGeneration.h ${Sources}/FileGenerations/FileGeneration.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/FileGenerations/FileGeneration.c -c ${Fsg} -o ${Sources}/FileGenerations/FileGeneration.o ${OpenSSL3}