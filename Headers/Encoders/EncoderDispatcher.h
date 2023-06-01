#pragma once
/**
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
  int isInitialized;

  int (*pf__encoder)(unsigned char*, int, unsigned char*, int*, unsigned char*);
  int (*pf__decoder)(unsigned char*, int, unsigned char*, int*, unsigned char*);
};

// Method definitions
void EncoderDispatcher__constructor(EncoderDispatcher*);
void EncoderDispatcher__destructor(const EncoderDispatcher*);

// External functions
extern void UU_Encode__constructor(UU_Encode*);