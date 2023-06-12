#pragma once
/** @file Encryption.h
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

  // Encryption function pointer for linking with the method of the child class
  int (*pf__encryption)(Encryption*, const unsigned char*, const int, unsigned char*, int*);
  // Decryption function pointer for linking with the method of the child class
  int (*pf__decryption)(Encryption*, unsigned char*, int, unsigned char*, int*);
  // The function pointer of server key initialization; this pointer is for linking with the method of the child class
  int (*pf__initializeServerKey)(Encryption*);
  // The function pointer of setting current working directory; this pointer is for linking with the method of the child class
  int (*pf__setProjectPath)(Encryption*, unsigned char*);
};

// Method declarations
void Encryption__extension(const Encryption*);
