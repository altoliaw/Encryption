#include "./Headers/Entry.h"

// Global variable
static EncryptionDispatcher __encryptionDispatcherObject__;
static EncoderDispatcher __encoderDispatcherObject__;

int ___AES_256_GCMWithUUEncode(
    const unsigned char* plainText,
    const int plainTextLen,
    unsigned char* encodedText,
    int* encodedTextLen)
{
    #define AES_256_GCM_IV_SIZE 12 // 96 bits
    #define AES_256_GCM_TAG_SIZE 16 // 128 bits

    int httpStatus = 200;
    unsigned char ciphertext[plainTextLen + AES_256_GCM_IV_SIZE + AES_256_GCM_TAG_SIZE + 1];
    int ciphertextLen = 0;
    httpStatus = ___encryption(plainText, plainTextLen, ciphertext, &ciphertextLen, (unsigned char*)"AES_256_GCM");
    if(httpStatus < 200 || httpStatus >= 300) {
        return httpStatus;
    }
    httpStatus = ___encoder(ciphertext, ciphertextLen, encodedText, encodedTextLen, (unsigned char*)"UU_Encode");
    return httpStatus;
}

int ___AES_256_GCMWithUUDecode(
    const unsigned char* encodedText,
    const int encodedTextLen,
    unsigned char* plainText,
    int* plainTextLen)
{
    #define UU_BIT_STEP 6
    #define DECIMAL_BIT_STEP 8
    int length = (encodedTextLen * UU_BIT_STEP / DECIMAL_BIT_STEP + 1);
    int httpStatus = 200;
    unsigned char ciphertext[length];
    int ciphertextLen = 0;
    httpStatus = ___decoder(encodedText, encodedTextLen, ciphertext, &ciphertextLen, (unsigned char*)"UU_Encode");

    if(httpStatus < 200 || httpStatus >= 300) {
        return httpStatus;
    }
    httpStatus = ___decryption(ciphertext, ciphertextLen, plainText, plainTextLen, (unsigned char*)"AES_256_GCM");
    return httpStatus;
}

/**
 * An entry point of encryption for dynamical links. (.so, or .dll)
 *
 * @param plaintext const unsigned char* The plaintext source for encryption
 * @param plaintextLen const int The length of the source string
 * @param ciphertext unsigned char* The ciphertext
 * @param ciphertextLen int* The length of the ciphertext string
 * @param approach unsigned char* The approaches for encryption;
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___encryption(
        const unsigned char* plaintext,
        const int plaintextLen,
        unsigned char* ciphertext,
        int* ciphertextLen,
        unsigned char* approach) {

    if(__encryptionDispatcherObject__.isInitialized != 1) {
        EncryptionDispatcher__constructor(&__encryptionDispatcherObject__);
    }

    int httpStatus = 500;
    httpStatus = __encryptionDispatcherObject__.pf__encryption(
        plaintext,
        plaintextLen,
        ciphertext,
        ciphertextLen,
        approach
    );
    return httpStatus;
}

/**
 * An entry point of decryption for dynamical links. (.so, or .dll)
 *
 * @param ciphertext const unsigned char* The ciphertext source for encryption
 * @param ciphertextLen int The length of the ciphertext string
 * @param plaintext unsigned char* The plaintext
 * @param plaintextLen int* The length of the plaintext
 * @param approach unsigned char* The approaches for decryption
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___decryption(
    unsigned char* ciphertext,
    int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen,
    unsigned char* approach) {

    if(__encryptionDispatcherObject__.isInitialized != 1) {
        EncryptionDispatcher__constructor(&__encryptionDispatcherObject__);
    }
    int httpStatus = 500;
    httpStatus = __encryptionDispatcherObject__.pf__decryption(
        ciphertext,
        ciphertextLen,
        plaintext,
        plaintextLen,
        approach
    );
    return httpStatus;
}

/**
 * Server key initialization
 *
 * @param approach unsigned char* The approaches for decryption
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___initializeServerKey(unsigned char* approach) {
    if(__encryptionDispatcherObject__.isInitialized != 1) {
        EncryptionDispatcher__constructor(&__encryptionDispatcherObject__);
    }
    int httpStatus = 500;
    httpStatus = __encryptionDispatcherObject__.pf__initializeServerKey(approach);
    return httpStatus;
}

/**
 * Project path setting
 *
 * @param approach unsigned char* The approaches for decryption
 * @param projectPath unsigned char* The project path
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___setProjectPath(unsigned char* approach, unsigned char* projectPath) {
    if(__encryptionDispatcherObject__.isInitialized != 1) {
        EncryptionDispatcher__constructor(&__encryptionDispatcherObject__);
    }

    int httpStatus = 500;
    httpStatus = __encryptionDispatcherObject__.pf__setProjectPath(approach, projectPath);
    return httpStatus;
}

int ___encoder(
        unsigned char* plainText,
        int plainTextLen,
        unsigned char* encodedText,
        int* encodedTextLen,
        unsigned char* approach) {

    if(__encoderDispatcherObject__.isInitialized != 1) {
        EncoderDispatcher__constructor(&__encoderDispatcherObject__);
    }

    int httpStatus = 500;

    httpStatus = __encoderDispatcherObject__.pf__encoder(
        plainText,
        plainTextLen,
        encodedText,
        encodedTextLen,
        approach
    );
    return httpStatus;
}

int ___decoder(
        const unsigned char* encodedText,
        int encodedTextLen,
        unsigned char* plainText,
        int* plainTextLen,
        unsigned char* approach) {

    if(__encoderDispatcherObject__.isInitialized != 1) {
        EncoderDispatcher__constructor(&__encoderDispatcherObject__);
    }

    int httpStatus = 500;
    httpStatus = __encoderDispatcherObject__.pf__decoder(
        encodedText,
        encodedTextLen,
        plainText,
        plainTextLen,
        approach
    );
    return httpStatus;
}