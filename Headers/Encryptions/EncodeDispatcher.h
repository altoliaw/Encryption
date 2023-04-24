#pragma once
/**
 * To support multiple encode approaches, all encoding classes are modelled in the factory pattern.
 * This class is a dispatcher and determines which type of encoding object shall be generated.
 *
 * @author Nick
 * @date 2023/4/10
 */

// Files included
#include "./Encode.h"
#include "./AES_256_GCM.h"

// Class declarations
typedef struct EncodeDispatcher EncodeDispatcher;

// Class body
struct EncodeDispatcher {

  // Public variables to constructor/destructor functions
  int (*pf__encryption)(const unsigned char*, const int, unsigned char*, int*, unsigned char*, unsigned char*);
  int (*pf__decryption)(unsigned char*, int, unsigned char*, int*, unsigned char*, unsigned char*);
  int (*pf__initializeServerKey)(unsigned char*);
};

// Method declarations
void EncodeDispatcher__constructor(EncodeDispatcher*);
void EncodeDispatcher__destructor(const EncodeDispatcher*);

// External functions
extern void AES_256_GCM__constructor(AES_256_GCM* a2gObject);