#include "../../Headers/Encryptions/EncodeDispatcher.h"

static int EncodeDispatcher_encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*, unsigned char*);
static int EncodeDispatcher_decryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*, unsigned char*);
static int EncodeDispatcher_initializeServerKey(unsigned char*);
static int (*EncodeDispatcher_encryptedDispatcher(unsigned char*, Encode*))(Encode*, const unsigned char*, const int, unsigned char*, int*, unsigned char*);
static int (*EncodeDispatcher_decryptedDispatcher(unsigned char*, Encode*))(Encode*, const unsigned char*, const int, unsigned char*, int*, unsigned char*);
static int (*EncodeDispatcher_initializeServerKeyDispatcher(unsigned char*, Encode*))(Encode*);
static Encode* EncodeDispatcher_createEncryptedObject(unsigned char*);

void EncodeDispatcher__constructor(EncodeDispatcher* encObject)
{
    encObject->pf__encryption = &EncodeDispatcher_encryption;
    encObject->pf__decryption = &EncodeDispatcher_decryption;
    encObject->pf__initializeServerKey = &EncodeDispatcher_initializeServerKey;
}

void EncodeDispatcher__destructor(const EncodeDispatcher*)
{
    // Empty destructor
}

/**
 * Encryption function
 *
 * @param plaintext const unsigned char* The plaintext source for encryption
 * @param sourceLen const int The length of the source string
 * @param ciphertext unsigned char* The ciphertext
 * @param ciphertextLen int* The length of the ciphertext string
 * @param authTag unsigned char* The authentication tag
 * @param approach unsigned char* The approaches for encryption;
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncodeDispatcher_encryption(
    const unsigned char* plaintext,
    const int plaintextLen,
    unsigned char* ciphertext,
    int* ciphertextLen,
    unsigned char* authTag,
    unsigned char* approach)
{

    Encode* pEnc = NULL;
    pEnc = EncodeDispatcher_createEncryptedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encode*, const unsigned char*, const int, unsigned char*, int*, unsigned char*);
    dispatcher = EncodeDispatcher_encryptedDispatcher(approach, pEnc);
    int httpStatus = dispatcher(pEnc, plaintext, plaintextLen, ciphertext, ciphertextLen, authTag);

    return httpStatus;
}

/**
 * Decryption function
 *
 * @param ciphertext const unsigned char* The ciphertext source for encryption
 * @param ciphertextLen const int The length of the ciphertext string
 * @param plaintext unsigned char* The plaintext
 * @param plaintextLen int* The length of the plaintext
 * @param authTag unsigned char* The authentication tag
 * @param approach unsigned char* The approaches for decryption; nowadays,
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncodeDispatcher_decryption(
    const unsigned char* ciphertext,
    const int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen,
    unsigned char* authTag,
    unsigned char* approach)
{

    Encode* pEnc = NULL;
    pEnc = EncodeDispatcher_createEncryptedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encode*, const unsigned char*, const int, unsigned char*, int*, unsigned char*);
    dispatcher = EncodeDispatcher_decryptedDispatcher(approach, pEnc);
    int httpStatus = dispatcher(pEnc, ciphertext, ciphertextLen, plaintext, plaintextLen, authTag);

    return httpStatus;
}

/**
 * Key generation initialization
 *
 * @param approach unsigned char* The approaches for decryption; nowadays,
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncodeDispatcher_initializeServerKey(unsigned char* approach)
{
    Encode* pEnc = NULL;
    pEnc = EncodeDispatcher_createEncryptedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encode*);
    dispatcher = EncodeDispatcher_initializeServerKeyDispatcher(approach, pEnc);
    int httpStatus = dispatcher(pEnc);

    return httpStatus;
}

/**
 * Encryption Dispatcher
 *
 * @param approach unsigned char* The approaches for encryption
 * @param pEnv Encode* The address of the encryption object
 * @param pEnv Encode* The address of the encryption object
 * @param plaintext const unsigned char* The ciphertext source for encryption
 * @param plaintextLen const int The length of the source string
 * @param ciphertext unsigned char* The plaintext target
 * @param ciphertextLen int* The length of the target string; nowadays
 * @param authTag unsigned char* The authentication tag
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncodeDispatcher_encryptedDispatcher(unsigned char* approach, Encode* pEnc))(Encode* pEnc,
    const unsigned char* plaintext,
    const int plaintextLen,
    unsigned char* ciphertext,
    int* ciphertextLen,
    unsigned char* authTag)
{

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        AES_256_GCM* pa2gObject = NULL;
        pa2gObject = (AES_256_GCM*)pEnc;
        return (pa2gObject->o_Encode).pf__encryption; // Passing the execution of AES encryption
    } else {
        return NULL;
    }
}

/**
 * Decryption Dispatcher
 *
 * @param approach unsigned char* The approaches for decryption
 * @param pEnv Encode* The address of the decryption object
 * @param ciphertext const unsigned char* The ciphertext source for decryption
 * @param ciphertextLen const int The length of the source string
 * @param plaintext unsigned char* The plaintext target
 * @param plaintextLen int* The length of the target string; nowadays
 * @param authTag unsigned char* The authentication tag
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncodeDispatcher_decryptedDispatcher(unsigned char* approach, Encode* pEnc))(
    Encode* pEnc,
    const unsigned char* ciphertext,
    const int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen,
    unsigned char* authTag)
{

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        AES_256_GCM* pa2gObject = NULL;
        pa2gObject = (AES_256_GCM*)pEnc;
        return (pa2gObject->o_Encode).pf__decryption; // Pass the execution of AES encryption
    } else {
        return NULL;
    }
    return 0;
}

/**
 * Key generation initialization dispatcher
 *
 * @param approach unsigned char* The approaches for decryption
 * @param pEnv Encode* The address of the decryption object
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncodeDispatcher_initializeServerKeyDispatcher(unsigned char* approach, Encode* pEnc))(
    Encode* pEnc)
{

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        AES_256_GCM* pa2gObject = NULL;
        pa2gObject = (AES_256_GCM*)pEnc;
        return (pa2gObject->o_Encode).pf__initializeServerKey; // Pass the execution of AES encryption
    } else {
        return NULL;
    }
    return 0;
}

/**
 * Creating child object and converting a child object pointer to a parent pointer
 *
 * @param approach unsigned char* The approach for encryption
 * @return Encode* The address of the parent object shall be passed
 */
static Encode* EncodeDispatcher_createEncryptedObject(unsigned char* approach)
{
    Encode* pObject = NULL;

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        static AES_256_GCM __a2gObject;
        AES_256_GCM__constructor(&__a2gObject);
        pObject = (Encode*)(&__a2gObject);
    }
    return pObject;
}