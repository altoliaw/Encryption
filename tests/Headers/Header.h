#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "./test_Encoders_UU_Encode.h"
#include "./test_Entry.h"

extern void test_Encoders_UU_Encode_CompleteProcess(void**);
extern void test_Entry_UU_Encode(void**);
extern void test_Entry_UU_Encode_CompleteProcess(void**);
extern void test_Entry_UU_AES_GCM_256_CompleteProcess(void**);