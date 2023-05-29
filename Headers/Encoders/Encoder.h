#pragma once
/**
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
  int (*pf__encoder)(Encoder*, unsigned char*, int, unsigned char*, int*);
  int (*pf__decoder)(Encoder*, unsigned char*, int, unsigned char*, int*);
};

// Method declarations
void Encoder__extension(const Encoder*);