#include "./Headers/Entry.h"

/**
 * Main function
*/
int main(int argc, char *argv[]) {
    int iHttpNum = 0;
    /*
    unsigned char plainText [] = "Catagg44`\0";
    int plainTextLen = (int)strlen((char*)plainText);
    unsigned char encodedText [200];
    int encodedTextLen = 0;

    iHttpNum = ___encoder(plainText,
        plainTextLen,
        encodedText,
        &encodedTextLen,
        (unsigned char *)"UU_Encode");
    fprintf(stderr, "iHttpNum = %d\n", iHttpNum);
    fprintf(stderr, "encodedText = %s and total length = %d\n", encodedText, encodedTextLen);
    //==========================
    unsigned char plainText2 [200];
    int plainText2Len = 0;
    int encodedTextLen2 = (int)strlen((char*)encodedText);
    iHttpNum = ___decoder(encodedText,
        encodedTextLen2,
        plainText2,
        &plainText2Len,
        (unsigned char *)"UU_Encode");
    fprintf(stderr, "iHttpNum = %d\n", iHttpNum);
    fprintf(stderr, "decodedText = %s and total length = %d\n", plainText2, plainText2Len);
    */

    // ===========================
    //unsigned char* projectPath = (unsigned char*)"/home/nick/Workspace/C/Encryption";
    //iHttpNum = ___setProjectPath((unsigned char*)"AES_256_GCM", projectPath);
    //printf("http code is %d\n", iHttpNum);
    //iHttpNum = ___initializeServerKey((unsigned char*)"AES_256_GCM");
    //printf("http code is %d\n", iHttpNum);


    int iLen = 0;
    unsigned char buffer[2060];
    unsigned char tag[16];
    memset(buffer,'\0', 2060);
    unsigned char* str = (unsigned char*)"bbbbbb is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;";
    iHttpNum = 0;
    printf("The plaintext is %d\n", (int)strlen((char*)str));

    iHttpNum = ___encryption(
        str,
        (int)strlen((char *)str),
        buffer,
        &iLen,
        tag,
        (unsigned char*)"AES_256_GCM"
    );

    if (iHttpNum == 200) {
        printf("The ciphertext is  %s\n", buffer);
        printf("The length of the cipherText %d\n", iLen);
    }

//    //================================================================
    printf("========================================================\n");
    unsigned char decryptedBuffer[2060];
    memset(decryptedBuffer,'\0', 2060);
    unsigned char tag2[16];
    int iDLen = 0;

    iHttpNum = ___decryption(
        buffer,
        iLen,
        decryptedBuffer,
        &iDLen,
        tag2,
        (unsigned char* )"AES_256_GCM"
    );

    printf("HttpNum is %d\n", iHttpNum);
    if (iHttpNum == 200) {
        printf("The plaintext is %s\n", decryptedBuffer);
        printf("The length of the plainText %d\n", iDLen);
    }

    return 0;
}