#pragma once
/**
 * Abstract implementation of the encoding class in C
 *
 * @author Nick
 * @date 2023/4/17
 */

// Libraries included
#include <stdlib.h>
#include <string.h>

// Class declarations
typedef struct Encode Encode;

// Class body
struct Encode {

  // Public variables to constructor/destructor functions
  int (*pf__encryption)(Encode*, const unsigned char*, const int, unsigned char*, int*, unsigned char*);
  int (*pf__decryption)(Encode*, const unsigned char*, const int, unsigned char*, int*, unsigned char*);


  // Protected variables
  unsigned char* priKey;
  unsigned char* priKeyLoc;

  // Protected variables to constructor/destructor functions
  void (*pf_getPrivKey)(unsigned char*);
  int (*pf_checkPrivKeyExisted)();
  int (*pf_generatePrivKey)(unsigned char*);

};

// Method declarations
void Encode__extension(const Encode*);
