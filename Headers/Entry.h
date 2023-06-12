#pragma once
/** @file Entry.h
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
  // AES_256_GCM + UUEncoding
  EXPORT int ___AES_256_GCMWithUUEncode(const unsigned char*, const int, unsigned char*, int*);
  EXPORT int ___AES_256_GCMWithUUDecode(const unsigned char*, const int, unsigned char*, int*);
  // AES_256_GCM + UUEncoding
  EXPORT int ___AES_256_GCM(const unsigned char*, const int, unsigned char*);
  EXPORT int ___AES_256_GCM(const unsigned char*, const int, unsigned char*);
  // Encryption
  EXPORT int ___encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*);
  EXPORT int ___decryption(unsigned char*, int, unsigned char*, int*, unsigned char*);
  EXPORT int ___initializeServerKey(unsigned char*);
  EXPORT int ___setProjectPath(unsigned char*, unsigned char*);
  // Encode
  EXPORT int ___encoder(unsigned char*, int, unsigned char*, int*, unsigned char*);
  EXPORT int ___decoder(const unsigned char*, int, unsigned char*, int*, unsigned char*);

#else
  // AES_256_GCM + UUEncoding
  __attribute__((visibility("default"))) int ___AES_256_GCMWithUUEncode(const unsigned char*, const int, unsigned char*, int*);
  __attribute__((visibility("default"))) int ___AES_256_GCMWithUUDecode(const unsigned char*, const int, unsigned char*, int*);

  // AES_256_GCM
  __attribute__((visibility("default"))) int ___AES_256_GCM(const unsigned char*, const int, unsigned char*);
  __attribute__((visibility("default"))) int ___AES_256_GCM(const unsigned char*, const int, unsigned char*);

  // Encryption
  __attribute__((visibility("default"))) int ___encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*);
  __attribute__((visibility("default"))) int ___decryption(unsigned char*, int, unsigned char*, int*, unsigned char*);
  __attribute__((visibility("default"))) int ___initializeServerKey(unsigned char*);
  __attribute__((visibility("default"))) int ___setProjectPath(unsigned char*, unsigned char*);
  //Encode
  __attribute__((visibility("default"))) int ___encoder(unsigned char*, int, unsigned char*, int*, unsigned char*);
  __attribute__((visibility("default"))) int ___decoder(const unsigned char*, int, unsigned char*, int*, unsigned char*);
#endif