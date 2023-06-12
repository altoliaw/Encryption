#pragma once
/** @file UU_Encode.h
 * The UU_Encoded encoder and decoder,the algorithm of the UU encoder can be referred
 * in the following URL. {@url: https://en.wikipedia.org/wiki/Uuencoding}
 * (The algorithm in the URL belongs to the English version. Please refer to the English version
 * because the algorithm in English version is different to the one in Chinese version)
 *
 * @author Nick
 * @date 2023/5/29
 */

// Libraries included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Files included
#include "Encoder.h"

// Macro Definitions
// UUencode bit size
#define UU_BIT_STEP 6
// Traditional bit size
#define DECIMAL_BIT_STEP 8

// Class declarations
typedef struct UU_Encode UU_Encode;

// Class body
struct UU_Encode {
    // A flag to determine if the class is initialized
    int isInitialized;

    // An interface of UU_Encode
    Encoder oEncoder;

    // Pointer to the encode function
    int (*pf__encode)(char*, int, char*, int*);

    // Pointer to the decode function
    int (*pf__decode)(char*, int, char*, int*);
};

// Method declarations
void UU_Encode__constructor(UU_Encode*);
void UU_Encode__destructor(const UU_Encode*);

// External variables & functions
extern void Encoder__extension(const Encoder*);
