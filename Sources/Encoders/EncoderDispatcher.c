#include "../../Headers/Encoders/EncoderDispatcher.h"

// Method definitions
static int EncoderDispatcher_encoder(const unsigned char*, int, unsigned char*, int*, unsigned char*);
static int (*EncoderDispatcher_encodedDispatcher(unsigned char*, Encoder*))(const Encoder*, const unsigned char*, int, unsigned char*, int*);
static int EncoderDispatcher_decoder(const unsigned char*, int, unsigned char*, int*, unsigned char*);
static int (*EncoderDispatcher_decodedDispatcher(unsigned char*, Encoder*))(const Encoder*, const unsigned char*, int, unsigned char*, int*);
static Encoder* EncoderDispatcher_createEncodedObject(unsigned char*);

void EncoderDispatcher__constructor(EncoderDispatcher* encoderDispatcher)
{
    encoderDispatcher->isInitialized = 1;

    encoderDispatcher->pf__encoder = &EncoderDispatcher_encoder;
    encoderDispatcher->pf__decoder = &EncoderDispatcher_decoder;
}
void EncoderDispatcher__destructor(const EncoderDispatcher*)
{
    // TODO
}

/**
 * Encoder entry from outside functions; nowadays, only `UU_Encode` is available.
 *
 * @param plainText unsigned char* The plaintext
 * @param plainTextLen int The length if the plaintext
 * @param encodedText unsigned char* The encoded text, the parameter shall be allocated the size of memory outside.
 * The output format is modeled in `${encodedText:numeric}|${encodedText: char*}`. Assume the encoded function
 * is defined as f(.), ${encodedText:numeric} is the length of encoded text after f(.) and the
 * ${encodedText: char*} shows the encoded text after f(.). The length of the encoded text is variable because the length of
 * ${encodedText:numeric} depends on the length of f(.) encoded text.
 * @param encodedTextLen int The length of encoded text, including the length of `${encodedText:numeric}|`
 * @param approach unsigned char* The encoding approach
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncoderDispatcher_encoder(
    const unsigned char* plainText,
    int plainTextLen,
    unsigned char* encodedText,
    int* encodedTextLen,
    unsigned char* approach)
{
    int httpStatus = 200;
    Encoder* pEnc = NULL;
    pEnc = EncoderDispatcher_createEncodedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(const Encoder*, const unsigned char*, int, unsigned char*, int*);
    dispatcher = EncoderDispatcher_encodedDispatcher(approach, pEnc);
    httpStatus = dispatcher(pEnc, plainText, plainTextLen, encodedText, encodedTextLen);
    return httpStatus;
}

/**
 * Decoder entry from outside functions; nowadays, only `UU_Encode` is available.
 *
 * @param approach unsigned char* The approach for encoding
 * @param pEnc Encode* The parent type for recording the child object
 * @param plainText unsigned char* The plaintext
 * @param plainTextLen int The length of the plaintext
 * @param cipherText unsigned char* The ciphertext; the format is same as the one in function, EncoderDispatcher_encoder.
 * Please refer to the function, EncoderDispatcher_encoder
 * @param cipherTextLen int The length of ciphertext, including the length of `${encodedText:numeric}|`
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncoderDispatcher_encodedDispatcher(unsigned char* approach, Encoder* pEnc))(const Encoder* pEnc,
    const unsigned char* plainText,
    int plainTextLen,
    unsigned char* cipherText,
    int* cipherTextLen)
{
    if (!strcmp((char*)approach, "UU_Encode")) {
        UU_Encode* pu2eObject = NULL;
        pu2eObject = (UU_Encode*)pEnc;
        return (pu2eObject->oEncoder).pf__encoder; // Passing the execution of AES encryption
    } else {
        return NULL;
    }
    return 0;
}

/**
 * Decoder entry from outside functions; nowadays, only `UU_Encode` is available.
 *
 * @param encodedText unsigned char* The encoded text, the detail is denoted in the function, EncoderDispatcher_encoder
 * @param encodedTextLen int The length if the encoded text
 * @param plainText unsigned char* The plaintext before encoding
 * @param encodedTextLen int The length of encoded text, including the length of `${encodedText:numeric}|`
 * @param approach unsigned char* The encoding approach
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int EncoderDispatcher_decoder(
    const unsigned char* encodedText,
    int encodedTextLen,
    unsigned char* plainText,
    int* plainTextLen,
    unsigned char* approach)
{
    int httpStatus = 200;

    Encoder* pEnc = NULL;
    pEnc = EncoderDispatcher_createEncodedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(const Encoder*, const unsigned char*, int, unsigned char*, int*);
    dispatcher = EncoderDispatcher_decodedDispatcher(approach, pEnc);
    httpStatus = dispatcher(pEnc, encodedText, encodedTextLen, plainText, plainTextLen);
    return httpStatus;
}

/**
 * Decoder dispatcher; nowadays, only `UU_Encode` is available.
 *
 * @param approach unsigned char* The approach for encoding
 * @param pEnc Encode* The parent type for recording the child object
 * @param plainText unsigned char* The plaintext
 * @param plainTextLen int The length of the plaintext
 * @param cipherText unsigned char* The ciphertext; the format is same as the one in function, EncoderDispatcher_encoder.
 * Please refer to the function, EncoderDispatcher_encoder
 * @param cipherTextLen int The length of ciphertext, including the length of `${encodedText:numeric}|`
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int (*EncoderDispatcher_decodedDispatcher(unsigned char* approach, Encoder* pEnc))(const Encoder* pEnc,
    const unsigned char* cipherText,
    int cipherTextLen,
    unsigned char* plainText,
    int* plainTextLen)
{
    if (!strcmp((char*)approach, "UU_Encode")) {
        UU_Encode* pu2eObject = NULL;
        pu2eObject = (UU_Encode*)pEnc;
        return (pu2eObject->oEncoder).pf__decoder; // Passing the execution of UU_encode
    } else {
        return NULL;
    }
    return 0;
}

/**
 * Encoded object generation
 *
 * @param approach unsigned char* The approach for encoding
 * @return Encoder* The parent class for accepting child object
 */
static Encoder* EncoderDispatcher_createEncodedObject(unsigned char* approach)
{
    Encoder* pObject = NULL;
    if (!strcmp((char*)approach, "UU_Encode")) {
        static UU_Encode __u2eObject;
        if (__u2eObject.isInitialized != 1) {
            UU_Encode__constructor(&__u2eObject);
        }
        pObject = (Encoder*)(&__u2eObject);
    }
    return pObject;
}