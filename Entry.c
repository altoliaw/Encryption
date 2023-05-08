#include "./Headers/Entry.h"

// Global variable
static EncodeDispatcher __encDisObject__;

/**
 * An entry point of encryption for dynamical links. (.so, or .dll)
 *
 * @param plaintext const unsigned char* The plaintext source for encryption
 * @param plaintextLen const int The length of the source string
 * @param ciphertext unsigned char* The ciphertext
 * @param ciphertextLen int* The length of the ciphertext string
 * @param authTag unsigned char* The authentication tag
 * @param approach unsigned char* The approaches for encryption;
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___encryption(
        const unsigned char* plaintext,
        const int plaintextLen,
        unsigned char* ciphertext,
        int* ciphertextLen,
        unsigned char* tag,
        unsigned char* approach) {

    EncodeDispatcher__constructor(&__encDisObject__);

    int httpStatus = 0;
    httpStatus = __encDisObject__.pf__encryption(
        plaintext,
        plaintextLen,
        ciphertext,
        ciphertextLen,
        tag,
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
 * @param tag unsigned char* The authentication tag
 * @param approach unsigned char* The approaches for decryption; nowadays,
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int ___decryption(
    unsigned char* ciphertext,
    int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen,
    unsigned char* tag,
    unsigned char* approach) {

    EncodeDispatcher__constructor(&__encDisObject__);
    int httpStatus = 0;
    httpStatus = __encDisObject__.pf__decryption(
        ciphertext,
        ciphertextLen,
        plaintext,
        plaintextLen,
        tag,
        approach
    );
    return httpStatus;
}