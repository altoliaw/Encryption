#pragma once
/** @file EncoderDispatcher.h
 * The dispatcher of the encoder
 *
 * @author Nick
 * @date 2023/5/29
 */

// Libraries included
#include <stdio.h>

// Files included
#include "UU_Encode.h"

// Class definition
typedef struct EncoderDispatcher EncoderDispatcher;

// Class body
struct EncoderDispatcher {
  // A flag to determine if the class is initialized
  int isInitialized;

  // Pointer to the encoder function
  int (*pf__encoder)(const unsigned char*, int, unsigned char*, int*, unsigned char*);
  // Pointer to the decoder function
  int (*pf__decoder)(const unsigned char*, int, unsigned char*, int*, unsigned char*);
};

// Method definitions
void EncoderDispatcher__constructor(EncoderDispatcher*);
void EncoderDispatcher__destructor(const EncoderDispatcher*);

// External functions
extern void UU_Encode__constructor(UU_Encode*);