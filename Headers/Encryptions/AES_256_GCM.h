#pragma once
/** @file AES_256_GCM.h
 * The implementation of AES-256-GCM encryption
 *
 * @author Nick
 * @date 2023/4/17
 */

// Libraries included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Files included
#include "Encryption.h"
#include "../FileGenerations/FileGeneration.h"

// AES_256_GCM_KEY_SIZE has 256 bits
#define AES_256_GCM_KEY_SIZE 32
// AES_256_GCM_IV_SIZE has 96 bits
#define AES_256_GCM_IV_SIZE 12
// AES_256_GCM_TAG_SIZE has 128 bits
#define AES_256_GCM_TAG_SIZE 16
// The path where contains privacy key, the complete path is {current working directory path}/.privacy/.encryptionAES256GCM.bin
#define AES_256_GCM_KEY_LOCATION ".privacy/.encryptionAES256GCM.bin"

// Class definition
typedef struct AES_256_GCM AES_256_GCM;

// Class body
struct AES_256_GCM {
  // A flag to determine if the class is initialized
  int isInitialized;

  // An interface of AES_256_GCM
  Encryption o_Encryption;

  // Checking if the key file `.encryptionAES256GCM.bin` exists
  int (*pf__checkFileExisted)(AES_256_GCM*);

  // master key of AES_256_GCM
  unsigned char masterKey[AES_256_GCM_KEY_SIZE];

  // IO object
  FileGeneration fileGeneration;
};

// Method declarations
void AES_256_GCM__constructor(AES_256_GCM*);
void AES_256_GCM__destructor(const AES_256_GCM*);

// External variables & functions
extern void Encryption__extension(const Encryption*);
extern void FileGeneration__constructor(FileGeneration*);