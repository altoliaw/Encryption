#pragma once
/**
 * Definitions of functions as entries as API
 *
 * @author Nick
 * @date 2023/5/4
 */

// Libraries included
#include <stdio.h>

// Files included
#include "Header.h"

#if defined(_WIN32) || defined(_WIN64)
extern "C" {
  __declspec(dllexport) int ___encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*, unsigned char*);
  __declspec(dllexport) int ___decryption(unsigned char*, int, unsigned char*, int*, unsigned char*, unsigned char*);
}
#else
  __attribute__((visibility("default"))) int ___encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*, unsigned char*);
  __attribute__((visibility("default"))) int ___decryption(unsigned char*, int, unsigned char*, int*, unsigned char*, unsigned char*);
#endif