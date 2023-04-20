#include "./Headers/Header.h"

/**
 * Main function
*/
int main(int argc, char *argv[]) {

    static EncodeDispatcher encDisObject;
    EncodeDispatcher__constructor(&encDisObject);
    int iLen = 0;
    unsigned char buffer[1024];
    unsigned char tag[16];
    memset(buffer,'\0', 1024);
    unsigned char* str = "Louse is";
    int iHttpNum = 0;
    iHttpNum = encDisObject.pf__encryption(
        str,
        strlen((char *)str),
        buffer,
        &iLen,
        tag,
        (unsigned char*)"AES_256_GCM"
    );

    printf("en iHttpNum is %d\n", iHttpNum);
    if (iHttpNum == 200) {
        printf("The ciphertext is  %s\n", buffer);
        printf("The length of the cipherText %d\n", iLen);
    }

    //================================================================

    unsigned char decryptedBuffer[1024];
    memset(decryptedBuffer,'\0', 1024);
    int iDLen = 0;
    iHttpNum = 0;

    iHttpNum = encDisObject.pf__decryption(
        buffer,
        iLen,
        decryptedBuffer,
        &iDLen,
        tag,
        (unsigned char* )"AES_256_GCM"
    );

    if (iHttpNum == 200) {
        printf("The plaintext is %s\n", decryptedBuffer);
        printf("The length of the plainText %d\n", iDLen);
    }

   return 0;
}