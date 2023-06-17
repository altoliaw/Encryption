#include "./Headers/Header.h"

const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_Encoders_UU_Encode_CompleteProcess),
        cmocka_unit_test(test_Entry_UU_Encode),
        cmocka_unit_test(test_Entry_UU_Encode_CompleteProcess),
        cmocka_unit_test(test_Entry_UU_AES_GCM_256_CompleteProcess),
};

int main(void) {

    return cmocka_run_group_tests(tests, NULL, NULL);
}