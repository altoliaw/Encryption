#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include <string.h>

#include "../../Headers/Encoders/UU_Encode.h"

void test_Encoders_UU_Encode_CompleteProcess(void** state);

extern void UU_Encode__constructor(UU_Encode*);