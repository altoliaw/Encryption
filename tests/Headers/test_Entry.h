#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include <string.h>

#include "../../Headers/Entry.h"

void test_Entry_UU_Encode(void**);
void test_Entry_UU_Encode_CompleteProcess(void**);
void test_Entry_UU_AES_GCM_256_CompleteProcess(void**);


extern int ___encoder(unsigned char*, int, unsigned char*, int*, unsigned char*);
extern int ___decoder(const unsigned char*, int, unsigned char*, int*, unsigned char*);
extern int ___AES_256_GCM_encryption(const unsigned char*, const int, unsigned char*);
extern int ___AES_256_GCM_decryption(unsigned char*, const int, unsigned char*);

