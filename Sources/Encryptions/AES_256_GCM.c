#include "../../Headers/Encryptions/AES_256_GCM.h"

static int AES_256_GCM_encryption(Encode* ,const unsigned char*, const int, unsigned char*, int*, unsigned char*);
static int AES_256_GCM_decryption(Encode* ,const unsigned char*, const int, unsigned char*, int*, unsigned char*);

void AES_256_GCM__constructor(AES_256_GCM* a2gObject) {
    Encode__extension(&(a2gObject->o_Encode));
    (a2gObject->o_Encode).pf__encryption = &AES_256_GCM_encryption;
    (a2gObject->o_Encode).pf__decryption = &AES_256_GCM_decryption;
    a2gObject->masterKey = (unsigned char*)"0123456789abcdef0123456789abcdef";
    a2gObject->ivValue = (unsigned char*)"0123456789ab";
}

void AES_256_GCM__destructor(const AES_256_GCM*) {
    // Destructor function
}

/**
 * AES_256_GCM encryption
 *
 * @param pEnc Encode* The address of the encryption object
 * @param plaintext const unsigned char* The plaintext for the encryption
 * @param plaintextLen const int The length of the plaintext string
 * @param ciphertext unsigned char* The ciphertext
 * @param ciphertextLen int* The length of the ciphertext string
 * @param authTag unsigned char* The authentication tag
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_encryption(
        Encode* pEnc,
        const unsigned char* plaintext,
        const int plaintextLen,
        unsigned char* ciphertext,
        int* ciphertextLen,
        unsigned char* authTag) {

    AES_256_GCM const* pA2gObject = (AES_256_GCM*) pEnc;
    unsigned char const* key = pA2gObject->masterKey;
    unsigned char const* iv =  pA2gObject->ivValue;
    int currentLen = 0;
    int cipherLen = 0;

    EVP_CIPHER_CTX *ecCtx;

    // New an instance
    if(!(ecCtx = EVP_CIPHER_CTX_new())) {
        printf("EVP_CIPHER_CTX_new\n");
        return 500;
    }

    // Initialize encryption approach
    if(EVP_EncryptInit_ex(ecCtx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) {
        printf("EVP_EncryptInit_ex\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Set the GCM with the IV_SIZE
    if(EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_SET_IVLEN, IV_SIZE, NULL) != 1) {
        printf("EVP_CIPHER_CTX_ctrl\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Set the encryption key and iv values
    if(EVP_EncryptInit_ex(ecCtx, NULL, NULL, key, iv) != 1) {
        printf("EVP_EncryptInit_ex\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Encryption process
    if(EVP_EncryptUpdate(ecCtx, ciphertext, &currentLen, plaintext, plaintextLen) != 1){
        printf("EVP_EncryptUpdate\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }
    cipherLen = currentLen;

    // The last encryption of GCM
    if(EVP_EncryptFinal_ex(ecCtx, ciphertext + currentLen, &currentLen) != 1) {
        printf("EVP_EncryptFinal_ex\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }
    cipherLen += currentLen;

    // Insert authentication tag
    if(EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_GET_TAG, 16, authTag)!= 1) {
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Free the instance
    EVP_CIPHER_CTX_free(ecCtx);
    *ciphertextLen = cipherLen;

    return 200;
}

/**
 * AES_256_GCM decryption
 *
 * @param pEnc Encode* The address of the encryption object
 * @param ciphertext const unsigned char* The ciphertext
 * @param ciphertextLen const int The length of the ciphertext string
 * @param plaintext unsigned char* The plaintext for the encryption
 * @param plaintextLen int* The length of the plaintext string
 * @param authTag unsigned char* The authentication tag
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_decryption(
    Encode* pEnc,
    const unsigned char* ciphertext,
    const int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen,
    unsigned char* authTag) {

    AES_256_GCM const* pA2gObject = (AES_256_GCM*) pEnc;
    unsigned char const* key = pA2gObject->masterKey;
    unsigned char const* iv =  pA2gObject->ivValue;
    int currentLen = 0;
    int plainLen = 0;
    int decryptedStatus = 0;

    EVP_CIPHER_CTX* ecCtx;

    // New an instance
    if(!(ecCtx = EVP_CIPHER_CTX_new())) {
        printf("EVP_CIPHER_CTX_new\n");
        return 500;
    }

    // Initialise the decryption operation
    if(!EVP_DecryptInit_ex(ecCtx, EVP_aes_256_gcm(), NULL, NULL, NULL)) {
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Set iv length
    if(!EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_SET_IVLEN, IV_SIZE, NULL)) {
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Initializing key and iv
    if(!EVP_DecryptInit_ex(ecCtx, NULL, NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Providing the authenticated tag
    if(!EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_SET_TAG, TAG_SIZE, authTag)) {
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Decrypting plaintext
    if(!EVP_DecryptUpdate(ecCtx, plaintext, &currentLen, ciphertext, ciphertextLen)) {
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }
    plainLen = currentLen;

    // The last decryption of GCM
    decryptedStatus = EVP_DecryptFinal_ex(ecCtx, plaintext + currentLen, &currentLen);
    plainLen += currentLen;

    // free the instance
    EVP_CIPHER_CTX_free(ecCtx);

    *plaintextLen = plainLen;

    // Checking if the decrypted result was successful
    if(decryptedStatus > 0) {
        return 200;
    } else {
        return 500;
    }
}