#include "./Headers/Header.h"

/**
 * Main function
*/
int main(int argc, char *argv[]) {

    static EncodeDispatcher encDisObject;
    EncodeDispatcher__constructor(&encDisObject);

    encDisObject.pf__initializeServerKey((unsigned char*)"AES_256_GCM");

    int iLen = 0;
    unsigned char buffer[2060];
    unsigned char tag[16];
    memset(buffer,'\0', 2060);
    unsigned char* str = (unsigned char*)"a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;a is apple;";
    int iHttpNum = 0;
    printf("The plaintext is %d\n", (int)strlen((char*)str));

    iHttpNum = encDisObject.pf__encryption(
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

    //================================================================
    printf("========================================================\n");
    unsigned char decryptedBuffer[2060];
    memset(decryptedBuffer,'\0', 2060);
    int iDLen = 0;

    iHttpNum = encDisObject.pf__decryption(
        buffer,
        iLen,
        decryptedBuffer,
        &iDLen,
        tag,
        (unsigned char* )"AES_256_GCM"
    );

    printf("en iHttpNum is %d\n", iHttpNum);
    if (iHttpNum == 200) {
        printf("The plaintext is %s\n", decryptedBuffer);
        printf("The length of the plainText %d\n", iDLen);
    }

   return 0;
}