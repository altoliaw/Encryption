#include "../../Headers/Encryptions/EncryptionDispatcher.h"

static int EncryptionDispatcher_encryption(const unsigned char*, const int, unsigned char*, int*, unsigned char*);
static int EncryptionDispatcher_decryption(unsigned char*, int, unsigned char*, int*, unsigned char*);
static int EncryptionDispatcher_initializeServerKey(unsigned char*);
static int EncryptionDispatcher_setProjectPath(unsigned char*, unsigned char*);
static int (*EncryptionDispatcher_encryptedDispatcher(unsigned char*, Encryption*))(Encryption*, const unsigned char*, const int, unsigned char*, int*);
static int (*EncryptionDispatcher_decryptedDispatcher(unsigned char*, Encryption*))(Encryption*, unsigned char*, int, unsigned char*, int*);
static int (*EncryptionDispatcher_initializeServerKeyDispatcher(unsigned char*, Encryption*))(Encryption*);
static int (*EncryptionDispatcher_setProjectPathDispatcher(unsigned char* approach, Encryption* pEnc))(Encryption* pEnc, unsigned char* projectPath);
static Encryption* EncryptionDispatcher_createEncryptedObject(unsigned char*);

void EncryptionDispatcher__constructor(EncryptionDispatcher* encObject)
{
    encObject->isInitialized = 1;
    encObject->pf__encryption = &EncryptionDispatcher_encryption;
    encObject->pf__decryption = &EncryptionDispatcher_decryption;
    encObject->pf__initializeServerKey = &EncryptionDispatcher_initializeServerKey;
    encObject->pf__setProjectPath = &EncryptionDispatcher_setProjectPath;
}

void EncryptionDispatcher__destructor(const EncryptionDispatcher*)
{
    // Empty destructor
}

/**
 * Encryption function
 *
 * @param plaintext const unsigned char* The plaintext source for encryption
 * @param plaintextLen const int The length of the source string
 * @param ciphertext unsigned char* The ciphertext
 * @param ciphertextLen int* The length of the ciphertext string
 * @param approach unsigned char* The approaches for encryption;
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncryptionDispatcher_encryption(
    const unsigned char* plaintext,
    const int plaintextLen,
    unsigned char* ciphertext,
    int* ciphertextLen,
    unsigned char* approach)
{

    Encryption* pEnc = NULL;
    pEnc = EncryptionDispatcher_createEncryptedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encryption*, const unsigned char*, const int, unsigned char*, int*);
    dispatcher = EncryptionDispatcher_encryptedDispatcher(approach, pEnc);
    int httpStatus = dispatcher(pEnc, plaintext, plaintextLen, ciphertext, ciphertextLen);

    return httpStatus;
}

/**
 * Decryption function
 *
 * @param ciphertext const unsigned char* The ciphertext source for encryption
 * @param ciphertextLen const int The length of the ciphertext string
 * @param plaintext unsigned char* The plaintext
 * @param plaintextLen int* The length of the plaintext
 * @param approach unsigned char* The approaches for decryption; nowadays,
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncryptionDispatcher_decryption(
    unsigned char* ciphertext,
    int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen,
    unsigned char* approach)
{

    Encryption* pEnc = NULL;
    pEnc = EncryptionDispatcher_createEncryptedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encryption*, unsigned char*, int, unsigned char*, int*);
    dispatcher = EncryptionDispatcher_decryptedDispatcher(approach, pEnc);
    int httpStatus = dispatcher(pEnc, ciphertext, ciphertextLen, plaintext, plaintextLen);

    return httpStatus;
}

/**
 * Key generation initialization
 *
 * @param approach unsigned char* The approaches for decryption; nowadays, "AES_256_GCM" is acceptable.
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncryptionDispatcher_initializeServerKey(unsigned char* approach)
{
    Encryption* pEnc = NULL;
    pEnc = EncryptionDispatcher_createEncryptedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encryption*);
    dispatcher = EncryptionDispatcher_initializeServerKeyDispatcher(approach, pEnc);
    int httpStatus = dispatcher(pEnc);

    return httpStatus;
}

/**
 * Project path initialization
 *
 * @param approach unsigned char* The approaches for decryption; nowadays, "AES_256_GCM" is acceptable.
 * @param projectPath unsigned char* The project path
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncryptionDispatcher_setProjectPath(unsigned char* approach, unsigned char* projectPath)
{
    Encryption* pEnc = NULL;
    pEnc = EncryptionDispatcher_createEncryptedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encryption*, unsigned char*);
    dispatcher = EncryptionDispatcher_setProjectPathDispatcher(approach, pEnc);
    int httpStatus = dispatcher(pEnc, projectPath);

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
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncryptionDispatcher_encryptedDispatcher(unsigned char* approach, Encryption* pEnc))(Encryption* pEnc,
    const unsigned char* plaintext,
    const int plaintextLen,
    unsigned char* ciphertext,
    int* ciphertextLen)
{

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        AES_256_GCM* pa2gObject = NULL;
        pa2gObject = (AES_256_GCM*)pEnc;
        return (pa2gObject->o_Encryption).pf__encryption; // Passing the execution of AES encryption
    } else {
        return NULL;
    }
}

/**
 * Decryption Dispatcher
 *
 * @param approach unsigned char* The approaches for decryption
 * @param pEnv Encryption* The address of the decryption object
 * @param ciphertext const unsigned char* The ciphertext source for decryption
 * @param ciphertextLen const int The length of the source string
 * @param plaintext unsigned char* The plaintext target
 * @param plaintextLen int* The length of the target string; nowadays
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncryptionDispatcher_decryptedDispatcher(unsigned char* approach, Encryption* pEnc))(
    Encryption* pEnc,
    unsigned char* ciphertext,
    int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen)
{

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        AES_256_GCM* pa2gObject = NULL;
        pa2gObject = (AES_256_GCM*)pEnc;
        return (pa2gObject->o_Encryption).pf__decryption; // Pass the execution of AES encryption
    } else {
        return NULL;
    }
    return 0;
}

/**
 * Key generation initialization dispatcher
 *
 * @param approach unsigned char* The approaches for initializing the server key
 * @param pEnv Encryption* The address of the decryption object
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncryptionDispatcher_initializeServerKeyDispatcher(unsigned char* approach, Encryption* pEnc))(
    Encryption* pEnc)
{

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        AES_256_GCM* pa2gObject = NULL;
        pa2gObject = (AES_256_GCM*)pEnc;
        return (pa2gObject->o_Encryption).pf__initializeServerKey; // Pass the execution of AES server key initialization
    } else {
        return NULL;
    }
    return 0;
}

/**
 * Key generation initialization dispatcher
 *
 * @param approach unsigned char* The approaches for setting the project path
 * @param pEnv Encryption* The address of the decryption object
 * @param projectPath unsigned char* The project path
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncryptionDispatcher_setProjectPathDispatcher(unsigned char* approach, Encryption* pEnc))(
    Encryption* pEnc, unsigned char* projectPath)
{

    if (!strcmp((char*)approach, "AES_256_GCM")) {
        AES_256_GCM* pa2gObject = NULL;
        pa2gObject = (AES_256_GCM*)pEnc;
        return (pa2gObject->o_Encryption).pf__setProjectPath; // Pass the execution of AES server key initialization
    } else {
        return NULL;
    }
    return 0;
}

/**
 * Creating child object and converting a child object pointer to a parent pointer
 *
 * @param approach unsigned char* The approach for encryption, "AES_256_GCM" is acceptable.
 * @return Encryption* The address of the parent object shall be passed
 */
static Encryption* EncryptionDispatcher_createEncryptedObject(unsigned char* approach)
{
    Encryption* pObject = NULL;
    if (!strcmp((char*)approach, "AES_256_GCM")) {
        static AES_256_GCM __a2gObject;
        if (__a2gObject.isInitialized != 1) {
            AES_256_GCM__constructor(&__a2gObject);
        }
        pObject = (Encryption*)(&__a2gObject);
    }
    return pObject;
}