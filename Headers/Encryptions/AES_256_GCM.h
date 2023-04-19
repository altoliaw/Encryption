#pragma once
/**
 * The implementation of AES-256-GCM encryption
 *
 * @author Nick
 * @date 2023/4/17
 */

// Libraries included
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define KEY_SIZE 32 // 256 bits
#define IV_SIZE 12 // 96 bits
#define TAG_SIZE 16 // 128 bits

// Files included
#include "Encode.h"

// Class definition
typedef struct AES_256_GCM AES_256_GCM;

// Class body
struct AES_256_GCM {

  // Public variables
  Encode o_Encode;

  // Protected variables
  unsigned char* masterKey;
  unsigned char* masterKeyLoc;
  unsigned char* ivValue;
  unsigned char* ivValueLoc;
};

// Method declarations
void AES_256_GCM__constructor(AES_256_GCM*);
void AES_256_GCM__destructor(const AES_256_GCM*);

// External functions
extern void Encode__extension(const Encode*);