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
	make run

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
${Prdir}/${PjN}/build : 	${Prdir}/Entry.o \
							${Sources}/Encryptions/EncryptionDispatcher.o \
							${Sources}/Encryptions/Encryption.o \
							${Sources}/Encryptions/AES_256_GCM.o \
							${Sources}/FileGenerations/FileGeneration.o

# Create a module
${Prdir}/${PjN}: 	${Prdir}/Main.o \
					${Prdir}/Entry.o \
					${Sources}/Encryptions/EncryptionDispatcher.o \
					${Sources}/Encryptions/Encryption.o \
					${Sources}/Encryptions/AES_256_GCM.o \
					${Sources}/FileGenerations/FileGeneration.o

	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Fsg} -o ${Prdir}/${PjN} ${Prdir}/Main.o \
	${Prdir}/Entry.o \
	${Sources}/Encryptions/EncryptionDispatcher.o \
	${Sources}/Encryptions/Encryption.o \
	${Sources}/Encryptions/AES_256_GCM.o \
	${Sources}/FileGenerations/FileGeneration.o \
	-lssl -lcrypto

# Main
${Prdir}/Main.o:	${Headers}/Entry.h ${Prdir}/Main.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Prdir}/Main.c -c ${Fsg} -o ${Prdir}/Main.o

# Entry.o
${Prdir}/Entry.o:	${Headers}/Entry.h ${Headers}/Header.h ${Headers}/Encryptions/EncryptionDispatcher.h ${Prdir}/Entry.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Prdir}/Entry.c -c ${Fsg} -o ${Prdir}/Entry.o

# EncryptionDispatcher
${Sources}/Encryptions/EncryptionDispatcher.o:	${Headers}/Encryptions/EncryptionDispatcher.h ${Headers}/Encryptions/Encryption.h ${Headers}/Encryptions/AES_256_GCM.h ${Sources}/Encryptions/EncryptionDispatcher.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/Encryptions/EncryptionDispatcher.c -c ${Fsg} -o ${Sources}/Encryptions/EncryptionDispatcher.o ${OpenSSL3}

# Encryption
${Sources}/Encryptions/Encryption.o:	${Headers}/Encryptions/Encryption.h ${Headers}/Encryptions/Encryption.h ${Headers}/Encryptions/AES_256_GCM.h ${Sources}/Encryptions/Encryption.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/Encryptions/Encryption.c -c ${Fsg} -o ${Sources}/Encryptions/Encryption.o ${OpenSSL3}

# AES_256_GCM
${Sources}/Encryptions/AES_256_GCM.o:	${Headers}/FileGenerations/FileGeneration.h ${Headers}/Encryptions/AES_256_GCM.h ${Headers}/Encryptions/Encryption.h ${Sources}/Encryptions/AES_256_GCM.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/Encryptions/AES_256_GCM.c -c ${Fsg} -o ${Sources}/Encryptions/AES_256_GCM.o ${OpenSSL3}

# FileGeneration
${Sources}/FileGenerations/FileGeneration.o:	${Headers}/FileGenerations/FileGeneration.h ${Sources}/FileGenerations/FileGeneration.c
	${Cmp} ${Stdlib} ${Cmpopt} ${Detinfo} ${Wall} ${Sources}/FileGenerations/FileGeneration.c -c ${Fsg} -o ${Sources}/FileGenerations/FileGeneration.o ${OpenSSL3}