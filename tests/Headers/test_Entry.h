#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include <string.h>

#include "../../Headers/Entry.h"

extern int ___AES_256_GCMWithUUEncode(const unsigned char*, const int, unsigned char*, int*);
extern int ___AES_256_GCMWithUUDecode(unsigned char*, const int, unsigned char*, int*);



