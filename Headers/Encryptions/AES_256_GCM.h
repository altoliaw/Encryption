#pragma once
/**
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

#define AES_256_GCM_KEY_SIZE 32 // 256 bits
#define AES_256_GCM_IV_SIZE 12 // 96 bits
#define AES_256_GCM_TAG_SIZE 16 // 128 bits
#define AES_256_GCM_KEY_LOCATION ".privacy/.encryptionAES256GCM.bin" // {project}/.privacy/.encryptionAES256GCM.bin

// Files included
#include "Encode.h"
#include "../FileGenerations/FileGeneration.h"

// Class definition
typedef struct AES_256_GCM AES_256_GCM;

// Class body
struct AES_256_GCM {

  // Public variables
  Encode o_Encode;
  int (*pf__checkFileExisted)(AES_256_GCM*);

  // Protected variables
  unsigned char masterKey[AES_256_GCM_KEY_SIZE];
};

// Method declarations
void AES_256_GCM__constructor(AES_256_GCM*);
void AES_256_GCM__destructor(const AES_256_GCM*);

// External variables & functions
extern void Encode__extension(const Encode*);
extern void FileGeneration__constructor(FileGeneration*);