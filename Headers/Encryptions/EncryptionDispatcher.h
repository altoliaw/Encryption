#pragma once
/** @file EncryptionDispatcher.h
 * To support multiple encryption approaches, all encoding classes are modelled in the factory pattern.
 * This class is a dispatcher and determines which type of encoding object shall be generated.
 *
 * @author Nick
 * @date 2023/4/10
 */

// Files included
#include "./Encryption.h"
#include "./AES_256_GCM.h"

// Class declarations
typedef struct EncryptionDispatcher EncryptionDispatcher;

// Class body
struct EncryptionDispatcher {
  // // A flag to determine if the class is initialized
  int isInitialized;
  // Encryption Pointer
  int (*pf__encryption)(const unsigned char*, const int, unsigned char*, int*, unsigned char*);
  // Decryption Pointer
  int (*pf__decryption)(unsigned char*, int, unsigned char*, int*, unsigned char*);
  // Function pointer for linking server key of the suitable encryption approach
  int (*pf__initializeServerKey)(unsigned char*);
  // Function pointer for setting current working directory of the suitable encryption approach
  int (*pf__setProjectPath)(unsigned char*, unsigned char*);
};

// Method declarations
void EncryptionDispatcher__constructor(EncryptionDispatcher*);
void EncryptionDispatcher__destructor(const EncryptionDispatcher*);

// External functions
extern void AES_256_GCM__constructor(AES_256_GCM* a2gObject);