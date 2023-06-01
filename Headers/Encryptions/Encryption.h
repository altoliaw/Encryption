#pragma once
/**
 * Abstract implementation of the encryption class in C
 *
 * @author Nick
 * @date 2023/4/17
 */

// Libraries included
#include <stdlib.h>
#include <string.h>

// Class declarations
typedef struct Encryption Encryption;

// Class body
struct Encryption {

  // Public variables to constructor/destructor functions
  int (*pf__encryption)(Encryption*, const unsigned char*, const int, unsigned char*, int*);
  int (*pf__decryption)(Encryption*, unsigned char*, int, unsigned char*, int*);
  int (*pf__initializeServerKey)(Encryption*);
  int (*pf__setProjectPath)(Encryption*, unsigned char*);
};

// Method declarations
void Encryption__extension(const Encryption*);
