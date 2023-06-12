#pragma once
/** @file Encoder.h
 * Encoding text into a variable string without security issues
 *
 * @author Nick
 * @date 2023/5/26
 */

// Libraries included
#include <stdio.h>

// Class declarations
typedef struct Encoder Encoder;

// Class body
struct Encoder {
  // Pointer to encoder function
  int (*pf__encoder)(const Encoder*, const unsigned char*, int, unsigned char*, int*);
  // Pointer to decoder function
  int (*pf__decoder)(const Encoder*, const unsigned char*, int, unsigned char*, int*);
};

// Method declarations
void Encoder__extension(const Encoder*);