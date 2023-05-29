#include "../../Headers/Encoders/EncoderDispatcher.h"

// Method definitions
static int EncoderDispatcher_encoder(unsigned char*, int, unsigned char*, int*,unsigned char*);
static int (*EncoderDispatcher_encodedDispatcher(unsigned char*, Encoder*))(Encoder*, unsigned char*, int, unsigned char*,int*);
static int EncoderDispatcher_decoder(unsigned char*, int, unsigned char*, int*,unsigned char*);
static int (*EncoderDispatcher_decodedDispatcher(unsigned char*, Encoder*))(Encoder*, unsigned char*, int, unsigned char*,int*);
static Encoder* EncoderDispatcher_createEncodedObject(unsigned char*);

void EncoderDispatcher__constructor(EncoderDispatcher* encoderDispatcher) {
    encoderDispatcher->isInitialized = 1;

    encoderDispatcher->pf__encoder = &EncoderDispatcher_encoder;
    encoderDispatcher->pf__decoder = &EncoderDispatcher_decoder;
 }
void EncoderDispatcher__destructor(EncoderDispatcher*) {
    // TODO
}

int EncoderDispatcher_encoder(
    unsigned char* plainText,
    int plainTextLen,
    unsigned char* encodedText,
    int* encodedTextLen,
    unsigned char* approach)
{
    int httpStatus = 200;
    Encoder* pEnc = NULL;
    pEnc = EncoderDispatcher_createEncodedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encoder*, unsigned char*, int, unsigned char*, int*);
    dispatcher = EncoderDispatcher_encodedDispatcher(approach, pEnc);
    httpStatus = dispatcher(pEnc, plainText, plainTextLen, encodedText, encodedTextLen);
    return httpStatus;
}

static int (*EncoderDispatcher_encodedDispatcher(unsigned char* approach, Encoder* pEnc))(Encoder* pEnc,
    unsigned char* plainText,
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


static int EncoderDispatcher_decoder(
    unsigned char* encodedText,
    int encodedTextLen,
    unsigned char* plainText,
    int* plainTextLen,
    unsigned char* approach)
{
    int httpStatus = 200;

    Encoder* pEnc = NULL;
    pEnc = EncoderDispatcher_createEncodedObject(approach);

    // Definition of function variable & execution of the function
    int (*dispatcher)(Encoder*, unsigned char*, int, unsigned char*, int*);
    dispatcher = EncoderDispatcher_decodedDispatcher(approach, pEnc);
    httpStatus = dispatcher(pEnc, encodedText, encodedTextLen, plainText, plainTextLen);
    return httpStatus;
}

static int (*EncoderDispatcher_decodedDispatcher(unsigned char* approach, Encoder* pEnc))(Encoder* pEnc,
    unsigned char* plainText,
    int plainTextLen,
    unsigned char* cipherText,
    int* cipherTextLen)
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


static Encoder* EncoderDispatcher_createEncodedObject(unsigned char* approach)
{
    Encoder* pObject = NULL;
    if (!strcmp((char*)approach, "UU_Encode")) {
        static UU_Encode __u2eObject;
        if(__u2eObject.isInitialized != 1) {
            UU_Encode__constructor(&__u2eObject);
        }
        pObject = (Encoder*)(&__u2eObject);
    }
    return pObject;
}