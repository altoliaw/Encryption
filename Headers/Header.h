#pragma once
/**
 * A header of the dispatcher of the encrytion function
 *
 * @author Nick
 * @date 2023/4/10
 */

// Libraries inlined
#include <stdio.h>

// Files included
#include "./Encryptions/EncryptionDispatcher.h"
#include "./Encoders/EncoderDispatcher.h"
#include "./FileGenerations/FileGeneration.h"



extern void EncryptionDispatcher__constructor(EncryptionDispatcher*);
extern void EncoderDispatcher__constructor(EncoderDispatcher*);