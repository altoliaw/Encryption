#include "../Headers/test_Encoders_UU_Encode.h"


/**
 * Testing the encode & decode methods of UU_Encode
 *
 * @param state void** cmocka pointer
 */
void test_Encoders_UU_Encode_CompleteProcess(void** state)
{
    UU_Encode oUUEncode;
    UU_Encode__constructor(&oUUEncode);

    // Encode
    unsigned char plainText [] = "Cat\0";
    int plainTextLen = (int)strlen((char*)plainText);
    int encodedTextLen = 0;
    unsigned char encodedText [200];
    int httpStatus = 0;
    const Encoder* pEncoder = (Encoder*)(&oUUEncode);
    httpStatus = oUUEncode.oEncoder.pf__encoder(pEncoder, plainText, plainTextLen, encodedText, &encodedTextLen);
    assert_int_equal(httpStatus, 200);
    encodedText[encodedTextLen] = '\0';
    assert_string_equal("0V%T", encodedText);

    // Decode
    unsigned char resultPlaintext [200];
    int resultPlaintextLen = 0;
    httpStatus = oUUEncode.oEncoder.pf__decoder(pEncoder, encodedText, encodedTextLen, resultPlaintext, &resultPlaintextLen);
    assert_int_equal(httpStatus, 200);
    resultPlaintext[resultPlaintextLen] = '\0';
    assert_string_equal("Cat\0", resultPlaintext);
}