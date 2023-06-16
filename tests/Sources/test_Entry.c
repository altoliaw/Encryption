#include "../Headers/test_Entry.h"

/**
 * Testing the AES_256_GCMWithUU_Encode function
 *
 * @param state void** cmocka object pointer
 */
void test_Entry_AES_256_GCMWithUU_Encode(void** state)
{
    // Encode
    int iHttpNum = 0;
    unsigned char plainText [] = "Cat`\0";
    int plainTextLen = (int)strlen((char*)plainText);
    unsigned char encodedText [200];
    int encodedTextLen = 0;

    iHttpNum = ___AES_256_GCMWithUUEncode(plainText,
        plainTextLen,
        encodedText,
        &encodedTextLen);

    // Decode
    int encodedTextLen2 = (int)strlen((char*)encodedText);
    unsigned char plainText2 [200];
    int plainText2Len = 0;

    iHttpNum = ___AES_256_GCMWithUUDecode(
        encodedText,
        encodedTextLen2,
        plainText2,
        &plainText2Len
    );
    plainText2[plainText2Len] = '\0';
    assert_string_equal(plainText, plainText2);
}