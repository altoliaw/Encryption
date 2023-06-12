#include "./Headers/Entry.h"

// Global variable
static EncryptionDispatcher __encryptionDispatcherObject__;
static EncoderDispatcher __encoderDispatcherObject__;

/**
 * AES_256_GCM encryption; the length of the ciphertext is equal to the length of the
 * plaintext plus 28 which is the sum from the IV value(12) and the auth tag(16).
 *
 * @param plainText unsigned char* The plain text
 * @param plainTextLen int The length of the plain text
 * @param ciphertext unsigned char* The encrypted text; the size of the array shall be allocated in advance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___AES_256_GCM(
    const unsigned char* plainText,
    const int plainTextLen,
    unsigned char* ciphertext
    )
{
    int httpStatus = 200;
    unsigned char ciphertext[plainTextLen + AES_256_GCM_IV_SIZE + AES_256_GCM_TAG_SIZE + 1];
    int ciphertextLen = 0;
    httpStatus = ___encryption(plainText, plainTextLen, ciphertext, &ciphertextLen, (unsigned char*)"AES_256_GCM");
    return httpStatus;
}

/**
 * AES_256_GCM decryption; the length of the plaintext is equal to the length of the
 * ciphertext minus 28 which is the sum from the IV value(12) and the auth tag(16).
 *
 * @param ciphertext unsigned char* The cipher text; the size of the array shall be allocated in advance
 * @param ciphertextLen int The length of the encrypted text
 * @param plainText unsigned char* The plain text; the size of the array shall be allocated in advance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___AES_256_GCM(
    const unsigned char* ciphertext,
    const int ciphertextLen,
    unsigned char* plainText)
{
    int httpStatus = 200;
    int plainTextLen = 0;
    httpStatus = ___decryption(ciphertext, ciphertextLen, plainText, &plainTextLen, (unsigned char*)"AES_256_GCM");
    return httpStatus;
}

/**
 * AES_256_GCM encryption with UUencode
 *
 * @param plainText unsigned char* The plain text
 * @param plainTextLen int The length of the plain text
 * @param encodedText unsigned char* The encoded text; the size of the array shall be allocated in advance
 * @param encodedTextLen int* The length of the encoded text; the variable belongs to call-by the value of address
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
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

/**
 * AES_256_GCM decryption with UUdecode
 *
 * @param encodedText unsigned char* The encoded text; the size of the array shall be allocated in advance
 * @param encodedTextLen int The length of the encoded text
 * @param plainText unsigned char* The plain text; the size of the array shall be allocated in advance
 * @param plainTextLen int* The length of the plain text; the variable belongs to call-by the value of address
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
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

/**
 * Encoding the plaintext into the encoded text
 *
 * @param plainText unsigned char* The plaintext
 * @param plainTextLen int The length of the plaintext
 * @param encodedText unsigned char* The ciphertext which the size of the array shall be defined in advance
 * @param encodedTextLen int* The length of the ciphertext; the variable belongs to call-by the value of address
 * @param approach unsigned char* The approach; nowadays, only "UU_Encode" is available
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
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

/**
 * Decoding the encoded text into the plaintext
 *
 * @param encodedText unsigned char* The encoded text
 * @param encodedTextLen int The length of the encoded text
 * @param plainText unsigned char* The plain text; the size of variable shall be defined in advance
 * @param plainTextLen int* The length of the plain text; the variable shall be defined as call-by the value of address
 * @param approach unsigned char* The approach; nowadays, only "UU_Encode" is available
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
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