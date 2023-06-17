#include "../Headers/test_Entry.h"

/**
 * Testing the UU_Encode function
 *
 * @param state void** cmocka object pointer
 */
void test_Entry_UU_Encode(void** state)
{
    // Encode
    int httpStatus = 0;
    unsigned char plainText [] = "Cat`\0";
    int plainTextLen = (int)strlen((char*)plainText);
    unsigned char encodedText [200];
    int encodedTextLen = 0;

    httpStatus = ___encoder(plainText, plainTextLen, encodedText, &encodedTextLen, (unsigned char*)"UU_Encode");
    assert_int_equal(httpStatus, 200);

}

/**
 *  Testing the UU_Encode and UU_Decode functions
 *
 * @param state void** The pointer of the cmocka object
 */
void test_Entry_UU_Encode_CompleteProcess(void** state)
{
    // Encode
    int httpStatus = 0;
    unsigned char plainText [] = "Cat`\0";
    int plainTextLen = (int)strlen((char*)plainText);
    unsigned char encodedText [200];
    int encodedTextLen = 0;

    httpStatus = ___encoder(plainText, plainTextLen, encodedText, &encodedTextLen, (unsigned char*)"UU_Encode");

    // Decode
    int encodedTextLen2 = (int)strlen((char*)encodedText);
    unsigned char plainText2 [200];
    int plainText2Len = 0;

    httpStatus = ___decoder(encodedText, encodedTextLen2, plainText2, &plainText2Len, (unsigned char*)"UU_Encode");

    plainText2[plainText2Len] = '\0';
    assert_string_equal(plainText, plainText2);

}

/**
 * Testing the AES_GCM_256 function
 *
 * @param state void** The pointer of the cmocka object
 */
void test_Entry_UU_AES_GCM_256_CompleteProcess(void** state)
{
    unsigned char* plaintext = (unsigned char*)"bbbbbb is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;";
    int plaintextLen = (int)strlen((char*)plaintext);
    int httpStatus = 0;
    int ciphertextLen = plaintextLen + 28; // IV + auth tag
    unsigned char ciphertext[2060];
    memset(ciphertext, '\0', 2060);
    httpStatus = 0;

    httpStatus = ___AES_256_GCM_encryption(
        plaintext,
        plaintextLen,
        ciphertext
    );

    assert_int_equal(httpStatus, 200);

    unsigned char plaintext2[2060];
    memset(plaintext2, '\0', 2060);
    int plaintext2Len = plaintextLen + 1;
    plaintext2[plaintext2Len] = '\0';

    httpStatus =  ___AES_256_GCM_decryption(ciphertext, ciphertextLen, plaintext2);
    assert_int_equal(httpStatus, 200);
    assert_string_equal(plaintext2, plaintext);
}