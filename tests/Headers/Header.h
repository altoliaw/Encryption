#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>


extern void test_Encoders_UU_Encode_CompleteProcess(void** state);
extern void test_Entry_AES_256_GCMWithUU_Encode(void** state);