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
  #define EXPORT __declspec(dllexport)
  EXPORT int ___encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*, unsigned char*);
  EXPORT int ___decryption(unsigned char*, int, unsigned char*, int*, unsigned char*, unsigned char*);
  EXPORT int ___initializeServerKey(unsigned char*);
  EXPORT int ___setProjectPath(unsigned char*, unsigned char*);

  EXPORT int ___encoder(unsigned char*, int, unsigned char*, int*, unsigned char*);
  EXPORT int ___decoder(unsigned char*, int, unsigned char*, int*, unsigned char*);

#else
  __attribute__((visibility("default"))) int ___encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*, unsigned char*);
  __attribute__((visibility("default"))) int ___decryption(unsigned char*, int, unsigned char*, int*, unsigned char*, unsigned char*);
  __attribute__((visibility("default"))) int ___initializeServerKey(unsigned char*);
  __attribute__((visibility("default"))) int ___setProjectPath(unsigned char*, unsigned char*);

  __attribute__((visibility("default"))) int ___encoder(unsigned char*, int, unsigned char*, int*, unsigned char*);
  __attribute__((visibility("default"))) int ___decoder(unsigned char*, int, unsigned char*, int*, unsigned char*);
#endif