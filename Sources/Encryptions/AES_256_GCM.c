#include "../../Headers/Encryptions/AES_256_GCM.h"

static int AES_256_GCM_encryption(Encryption*, const unsigned char*, const int, unsigned char*, int*);
static int AES_256_GCM_decryption(Encryption*, unsigned char*, int, unsigned char*, int*);
static int AES_256_GCM_initializeMasterKey(Encryption*);
static int AES_256_GCM_setProjectPath(Encryption*, unsigned char*);
static int AES_256_GCM_generateMasterKey(AES_256_GCM*);
static int AES_256_GCM_getMasterKey(AES_256_GCM*);
static int AES_256_GCM_getIV(unsigned char*);
static int AES_256_GCM_checkFileExisted(AES_256_GCM*);
static int AES_256_GCM_readKeyFile(AES_256_GCM*);
static int AES_256_GCM_checkDirArchitecture(AES_256_GCM*);

void AES_256_GCM__constructor(AES_256_GCM* a2gObject)
{
    a2gObject->isInitialized = 1;

    // FileGeneration constructor
    if((a2gObject->fileGeneration).isInitialized != 1) {
        FileGeneration__constructor(&(a2gObject->fileGeneration));
    }

    // Inheritance
    Encryption__extension(&(a2gObject->o_Encryption));
    // Class methods overloading (parent class)
    (a2gObject->o_Encryption).pf__encryption = &AES_256_GCM_encryption;
    (a2gObject->o_Encryption).pf__decryption = &AES_256_GCM_decryption;
    (a2gObject->o_Encryption).pf__initializeServerKey = &AES_256_GCM_initializeMasterKey;
    (a2gObject->o_Encryption).pf__setProjectPath = &AES_256_GCM_setProjectPath;
    memset(a2gObject->masterKey, (unsigned char)'\0', AES_256_GCM_KEY_SIZE);

    // Class methods
    a2gObject->pf__checkFileExisted = &AES_256_GCM_checkFileExisted;
    AES_256_GCM_getMasterKey(a2gObject);
}

void AES_256_GCM__destructor(const AES_256_GCM* a2gObject)
{
    FileGeneration__destructor(&(a2gObject->fileGeneration));
}

/**
 * AES_256_GCM encryption
 *
 * @param pEnc Encryption* The address of the encryption object
 * @param plaintext const unsigned char* The plaintext for the encryption. The size of the array outside shall
 * preserved AES_256_GCM_IV_SIZE (12) and AES_256_GCM_TAG_SIZE(16) units. That is, if the fixed size is 1024 for the variable, plaintext,
 * the size of the array outside shall be 1024+12+16 = 1052 for the variable, ciphertext.
 * @param plaintextLen const int The length of the plaintext string
 * @param ciphertext unsigned char* The ciphertext
 * @param ciphertextLen int* The length of the ciphertext string
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_encryption(
    Encryption* pEnc,
    const unsigned char* plaintext,
    const int plaintextLen,
    unsigned char* ciphertext,
    int* ciphertextLen)
{
    int httpStatus = 500;
    AES_256_GCM* pA2gObject = (AES_256_GCM*)pEnc;
    unsigned char const* key = pA2gObject->masterKey;
    unsigned char authTag[AES_256_GCM_TAG_SIZE];// The tag for the ciphertext which can verify if the ciphertext had been modified in connection.

    httpStatus = AES_256_GCM_checkFileExisted(pA2gObject);
    if (httpStatus != 200) {
        //fprintf(stderr, "Key Lost.\n");
        return 500;
    }

    unsigned char iv[(AES_256_GCM_IV_SIZE + 1)]; // "+1" is for the symbol '\0'.
    memset(iv, (unsigned char)'\0', AES_256_GCM_IV_SIZE + 1);
    httpStatus = AES_256_GCM_getIV(iv);

    if (httpStatus == 200) {

        int currentLen = 0;
        int cipherLen = 0;

        EVP_CIPHER_CTX* ecCtx;

        // New an instance
        if (!(ecCtx = EVP_CIPHER_CTX_new())) {
            //fprintf(stderr, "EVP_CIPHER_CTX_new\n");
            return 500;
        }

        // Initialize encryption approach
        if (EVP_EncryptInit_ex(ecCtx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) {
            //fprintf(stderr, "EVP_EncryptInit_ex\n");
            EVP_CIPHER_CTX_free(ecCtx);
            return 500;
        }

        // Set the GCM with the IV_SIZE
        if (EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_SET_IVLEN, AES_256_GCM_IV_SIZE, NULL) != 1) {
            //fprintf(stderr, "EVP_CIPHER_CTX_ctrl\n");
            EVP_CIPHER_CTX_free(ecCtx);
            return 500;
        }

        // Set the encryption key and iv values
        if (EVP_EncryptInit_ex(ecCtx, NULL, NULL, key, iv) != 1) {
            //fprintf(stderr, "EVP_EncryptInit_ex\n");
            EVP_CIPHER_CTX_free(ecCtx);
            return 500;
        }

        // Encryption process
        if (EVP_EncryptUpdate(ecCtx, ciphertext, &currentLen, plaintext, plaintextLen) != 1) {
            //fprintf(stderr, "EVP_EncryptUpdate\n");
            EVP_CIPHER_CTX_free(ecCtx);
            return 500;
        }
        cipherLen = currentLen;

        // The last encryption of GCM
        if (EVP_EncryptFinal_ex(ecCtx, ciphertext + currentLen, &currentLen) != 1) {
            //fprintf(stderr, "EVP_EncryptFinal_ex\n");
            EVP_CIPHER_CTX_free(ecCtx);
            return 500;
        }
        cipherLen += currentLen;

        // Insert authentication tag
        if (EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_GET_TAG, 16, authTag) != 1) {
            //fprintf(stderr, "EVP_CIPHER_CTX_ctrl\n");
            EVP_CIPHER_CTX_free(ecCtx);
            return 500;
        }

        // Free the instance
        EVP_CIPHER_CTX_free(ecCtx);
        *ciphertextLen = cipherLen;

        // Adding the IV and auth values into variable sequentially, cipherText and modifying the variable, cipherTextLen
        // Due to SonarLint's suggestions, the size of the array shall be larger than 1.
        unsigned char tmpCipher[((unsigned int)cipherLen) + 1];
        memset(tmpCipher, (unsigned char)'\0', ((unsigned int)cipherLen) + 1);
        memcpy(tmpCipher, ciphertext, cipherLen);
        memset(ciphertext, (unsigned char)'\0', cipherLen);
        memcpy(ciphertext, iv, AES_256_GCM_IV_SIZE);
        memcpy((ciphertext + AES_256_GCM_IV_SIZE), authTag, AES_256_GCM_TAG_SIZE);
        memcpy((ciphertext + AES_256_GCM_IV_SIZE + AES_256_GCM_TAG_SIZE), tmpCipher, cipherLen);
        *ciphertextLen = *ciphertextLen + AES_256_GCM_IV_SIZE + AES_256_GCM_TAG_SIZE;

        return 200;
    } else {
        return 500;
    }
}

/**
 * AES_256_GCM decryption
 *
 * @param pEnc Encryption* The address of the encryption object
 * @param ciphertext const unsigned char* The ciphertext
 * @param ciphertextLen const int The length of the ciphertext string
 * @param plaintext unsigned char* The plaintext for the encryption
 * @param plaintextLen int* The length of the plaintext string
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_decryption(
    Encryption* pEnc,
    unsigned char* ciphertext,
    int ciphertextLen,
    unsigned char* plaintext,
    int* plaintextLen
    )
{

    AES_256_GCM* pA2gObject = (AES_256_GCM*)pEnc;
    unsigned char const* key = pA2gObject->masterKey;
    unsigned char authTag[AES_256_GCM_TAG_SIZE];// The tag for the ciphertext which can verify if the ciphertext had been modified in connection.

    int httpStatus = 500;
    httpStatus = AES_256_GCM_checkFileExisted(pA2gObject);
    if (httpStatus != 200) {
        //fprintf(stderr, "Key Lost.\n");
        return 500;
    }

    // Obtaining the IV value
    unsigned char iv[AES_256_GCM_IV_SIZE + 1];
    memset(iv, '\0', AES_256_GCM_IV_SIZE + 1);
    memcpy(iv, ciphertext, AES_256_GCM_IV_SIZE);

    // Obtaining the authTag value
    memset(authTag, '\0', AES_256_GCM_TAG_SIZE);
    memcpy(authTag, ciphertext + AES_256_GCM_IV_SIZE, AES_256_GCM_TAG_SIZE);

    // Removing the IV value from the variable, "ciphertext"
    unsigned char tmpCipher[ciphertextLen + 1];
    memset(tmpCipher, '\0', ciphertextLen + 1);

    // Copying and ignoring the IV value
    memcpy(tmpCipher, (ciphertext + AES_256_GCM_IV_SIZE + AES_256_GCM_TAG_SIZE), (ciphertextLen - AES_256_GCM_IV_SIZE - AES_256_GCM_TAG_SIZE));
    memset(ciphertext, '\0', ciphertextLen);
    memcpy(ciphertext, tmpCipher, (ciphertextLen - AES_256_GCM_IV_SIZE - AES_256_GCM_TAG_SIZE));
    ciphertextLen = (ciphertextLen - AES_256_GCM_IV_SIZE - AES_256_GCM_TAG_SIZE);

    int currentLen = 0;
    int plainLen = 0;
    int decryptedStatus = 0;

    EVP_CIPHER_CTX* ecCtx;

    // Creating an instance
    if (!(ecCtx = EVP_CIPHER_CTX_new())) {
        //fprintf(stderr, "EVP_CIPHER_CTX_new\n");
        return 500;
    }

    // Initializing the decryption operation
    if (!EVP_DecryptInit_ex(ecCtx, EVP_aes_256_gcm(), NULL, NULL, NULL)) {
        //fprintf(stderr, "EVP_DecryptInit_ex\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Setting iv length
    if (!EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_SET_IVLEN, AES_256_GCM_IV_SIZE, NULL)) {
        //fprintf(stderr, "EVP_CIPHER_CTX_ctrl\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Initializing key and iv
    if (!EVP_DecryptInit_ex(ecCtx, NULL, NULL, key, iv)) {
        //fprintf(stderr, "EVP_DecryptInit_ex\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Providing the authenticated tag
    if (!EVP_CIPHER_CTX_ctrl(ecCtx, EVP_CTRL_GCM_SET_TAG, AES_256_GCM_TAG_SIZE, authTag)) {
        //fprintf(stderr, "EVP_CIPHER_CTX_ctrl\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }

    // Decrypting plaintext
    if (!EVP_DecryptUpdate(ecCtx, plaintext, &currentLen, ciphertext, ciphertextLen)) {
        //fprintf(stderr, "EVP_DecryptUpdate\n");
        EVP_CIPHER_CTX_free(ecCtx);
        return 500;
    }
    plainLen = currentLen;

    // The last decryption phase of GCM
    decryptedStatus = EVP_DecryptFinal_ex(ecCtx, plaintext + currentLen, &currentLen);
    plainLen += currentLen;

    // free the instance
    EVP_CIPHER_CTX_free(ecCtx);

    *plaintextLen = plainLen;

    // Checking if the decrypted result was successful
    if (decryptedStatus > 0) {
        return 200;
    } else {
        //fprintf(stderr, "decrypted Status error\n");
        return 500;
    }
}

/**
 * AES_256_GCM master key generation approach; the generation consists of
 * twp phases. The first phase is key generation; the second phase is writing the
 * key information into the specified file.
 *
 * @param a2gObject AES_256_GCM* The address of the AES_256_GCM instance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_generateMasterKey(AES_256_GCM* a2gObject)
{
    int httpStatus = 500;
    httpStatus = RAND_bytes(a2gObject->masterKey, AES_256_GCM_KEY_SIZE);
    httpStatus = (httpStatus == 1) ? 200 : 500;
    if (httpStatus == 200) {
        httpStatus = (a2gObject->fileGeneration).pf__writeFile(&(a2gObject->fileGeneration), (unsigned char*)AES_256_GCM_KEY_LOCATION, a2gObject->masterKey, (int)sizeof(a2gObject->masterKey), (unsigned char*)"wb");
    }

    return httpStatus;
}

/**
 * Obtaining the AES_256_GCM master key
 *
 * @param a2gObject AES_256_GCM* The address of the AES_256_GCM instance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_getMasterKey(AES_256_GCM* a2gObject)
{
    int httpStatus = 500;
    int tmpKeyLength = 0;

    tmpKeyLength = (int)strlen((char*)a2gObject->masterKey);
    if (tmpKeyLength <= 0 && AES_256_GCM_checkFileExisted(a2gObject) == 200) {
        AES_256_GCM_readKeyFile(a2gObject);
        httpStatus = 200;
    }
    return httpStatus;
}

/**
 * Obtaining a random AES_256_GCM IV value
 *
 * @param pivValue unsigned char* The value of IV
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_getIV(unsigned char* pivValue)
{
    int httpStatus = 500;
    httpStatus = RAND_bytes(pivValue, AES_256_GCM_IV_SIZE);
    httpStatus = (httpStatus == 1) ? 200 : 500;

    return httpStatus;
}

/**
 * Checking if the master key file exists
 *
 * @param a2gObject AES_256_GCM* The address of the AES_256_GCM instance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_checkFileExisted(AES_256_GCM* a2gObject)
{
    int httpStatus = 500; // false flag
    httpStatus = (a2gObject->fileGeneration).pf__checkFileExisted(&(a2gObject->fileGeneration), (unsigned char*)AES_256_GCM_KEY_LOCATION);

    return httpStatus;
}

/**
 * Reading the key file
 *
 * @param a2gObject AES_256_GCM* The address of the AES_256_GCM instance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_readKeyFile(AES_256_GCM* a2gObject)
{
    int httpStatus = 500;
    if (AES_256_GCM_checkFileExisted(a2gObject) == 200) {
        (a2gObject->fileGeneration).pf__readFile(&(a2gObject->fileGeneration), (unsigned char*)AES_256_GCM_KEY_LOCATION, a2gObject->masterKey, (unsigned char*)"rb", 1, AES_256_GCM_KEY_SIZE);
    } else {
        //fprintf(stderr, "AES_256_GCM_readKeyFile\n");
        httpStatus = 500;
    }

    return httpStatus;
}

/**
 * Initialization of the key file in the installation process.
 *
 * @param pEnc Encryption* The address of the encryption object
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_initializeMasterKey(Encryption* pEnc)
{
    AES_256_GCM* a2gObject = NULL;
    a2gObject = (AES_256_GCM*)pEnc;
    int httpStatus = 500;

    if (AES_256_GCM_checkDirArchitecture(a2gObject) != 200) {
        //fprintf(stderr, "AES_256_GCM_checkDirArchitecture\n");
        return httpStatus;
    }

    httpStatus = AES_256_GCM_checkFileExisted(a2gObject);

    if (httpStatus == 500) {
        httpStatus = AES_256_GCM_generateMasterKey(a2gObject);
    }

    return httpStatus;
}

/**
 * Setting the project path
 *
 * @param pEnc Encryption* The address of the encryption object
 * @param projectPath unsigned char* The project path
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_setProjectPath(Encryption* pEnc, unsigned char* projectPath)
{
    AES_256_GCM* a2gObject = NULL;
    a2gObject = (AES_256_GCM*)pEnc;
    int httpStatus = 500;

    if (strcmp((char*)projectPath, "") == 0) {
        httpStatus = (a2gObject->fileGeneration).pf__setProjectPath(
            &(a2gObject->fileGeneration),
            (unsigned char*)""
        );
    } else {
        httpStatus = (a2gObject->fileGeneration).pf__setProjectPath(
            &(a2gObject->fileGeneration),
            projectPath
        );
    }

    AES_256_GCM_getMasterKey(a2gObject);
    return httpStatus;
}


/**
 * A process to maintain the directories from the path
 *
 * @param a2gObject AES_256_GCM* The address of the AES_256_GCM instance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int AES_256_GCM_checkDirArchitecture(AES_256_GCM* a2gObject)
{
    int httpStatus = 500;

    httpStatus = (a2gObject->fileGeneration).pf__checkDirArchitecture(
        &(a2gObject->fileGeneration),
        (unsigned char*)AES_256_GCM_KEY_LOCATION
    );
    return httpStatus;
}
