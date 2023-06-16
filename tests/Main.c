#include "./Headers/Header.h"

const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_Encoders_UU_Encode_CompleteProcess),
        //cmocka_unit_test(test_Entry_AES_256_GCMWithUU_Encode),
};

int main(void) {


    return cmocka_run_group_tests(tests, NULL, NULL);
}