#include "./Headers/Entry.h"

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    int iHttpNum = 0;
    unsigned char plainText [] = "Cat`\0";
    int plainTextLen = (int)strlen((char*)plainText);
    unsigned char encodedText [200];
    int encodedTextLen = 0;

    iHttpNum = ___AES_256_GCMWithUUEncode(plainText,
        plainTextLen,
        encodedText,
        &encodedTextLen);
    fprintf(stderr, "iHttpNum = %d\n", iHttpNum);
    fprintf(stderr, "encodedText = %.*s and total length = %d\n", encodedTextLen, encodedText, encodedTextLen);
    //==========================
    int encodedTextLen2 = (int)strlen((char*)encodedText);
    unsigned char plainText2 [200];
    int plainText2Len = 0;
    iHttpNum = ___AES_256_GCMWithUUDecode(encodedText,
        encodedTextLen2,
        plainText2,
        &plainText2Len);
    fprintf(stderr, "iHttpNum = %d\n", iHttpNum);
    fprintf(stderr, "decodedText = %s and total length = %d\n", plainText2, plainText2Len);


    // ===========================
    // unsigned char* projectPath = (unsigned char*)"/home/nick/Workspace/C/Encryption";
    // iHttpNum = ___setProjectPath((unsigned char*)"AES_256_GCM", projectPath);
    // printf("http code is %d\n", iHttpNum);
    // iHttpNum = ___initializeServerKey((unsigned char*)"AES_256_GCM");
    // printf("http code is %d\n", iHttpNum);

    /*
    int iLen = 0;
    unsigned char buffer[2060];
    memset(buffer, '\0', 2060);
    unsigned char* str = (unsigned char*)"bbbbbb is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;";
    iHttpNum = 0;
    printf("The plaintext is %d\n", (int)strlen((char*)str));

    iHttpNum = ___encryption(
        str,
        (int)strlen((char*)str),
        buffer,
        &iLen,
        (unsigned char*)"AES_256_GCM");

    if (iHttpNum == 200) {
        printf("The ciphertext is  %s\n", buffer);
        printf("The length of the cipherText %d\n", iLen);
    }

    //    //================================================================
    printf("========================================================\n");
    unsigned char decryptedBuffer[2060];
    memset(decryptedBuffer, '\0', 2060);
    int iDLen = 0;

    iHttpNum = ___decryption(
        buffer,
        iLen,
        decryptedBuffer,
        &iDLen,
        (unsigned char*)"AES_256_GCM");

    printf("HttpNum is %d\n", iHttpNum);
    if (iHttpNum == 200) {
        printf("The plaintext is %s\n", decryptedBuffer);
        printf("The length of the plainText %d\n", iDLen);
    }
    */
    return 0;
}