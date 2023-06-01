#include "../../Headers/Encoders/UU_Encode.h"

static int UU_Encode_encoder(Encoder*, const unsigned char*, int, unsigned char*, int*);
static int UU_Encode_decoder(Encoder*, const unsigned char*, int, unsigned char*, int*);

// Method definitions
void UU_Encode__constructor(UU_Encode* oUuEncoder)
{
    oUuEncoder->isInitialized = 1;

    Encoder__extension(&(oUuEncoder->oEncoder));
    (oUuEncoder->oEncoder).pf__encoder = &UU_Encode_encoder;
    (oUuEncoder->oEncoder).pf__decoder = &UU_Encode_decoder;
}
void UU_Encode__destructor(const UU_Encode*)
{
    // TODO
}

/**
 * UUencoded encoder
 *
 * @param oEncoder Encoder* The encoder object
 * @param plainText unsigned char* The plain text of encoder; the size of variable
 * shall be defined on the caller.
 * @param plainLen int The length of The plain text of encoder
 * @param encodedText unsigned char* The encoded text of encoder; the size of variable
 * shall be defined on the caller
 * @param encodedTextLen int The length of The encoded text of encoder; the variable belongs to
 * called-by-value of address
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
int UU_Encode_encoder(Encoder* oEncoder,
    const unsigned char* plainText, int plainLen, unsigned char* encodedText, int* encodedTextLen)
{
    /*
     * Reserving a character size (8 bit) in advance,
     * and the buffer is modeled as a cyclic storage;
     * as a result, the size of the inputBitBuffer equals to 2 * DECIMAL_BIT_STEP
     */
    unsigned char inputBitBuffer[(DECIMAL_BIT_STEP + DECIMAL_BIT_STEP)];
    int totalBits = (plainLen * DECIMAL_BIT_STEP); // The size of the total bits of plainText
    // Prediction of the encoded length
    *encodedTextLen = (totalBits % UU_BIT_STEP == 0) ? (totalBits / UU_BIT_STEP) : (totalBits / UU_BIT_STEP + 1);
    encodedText[*encodedTextLen + 1] = (unsigned char)'\0'; // The size is equal to `*encodedTextLen + 1` because the last element is for the '\0'.

    int startElementIndex = 0; // The index of the starting element
    int endElementIndex = 0; // The index of the last element
    memset(inputBitBuffer, '\0', 2 * DECIMAL_BIT_STEP);
    int remainder = 0; // The remainder elements in the stack
    int transIndex = 0; // The index for inputBitBuffer

    // Loop over all plainText characters
    for (int i = 0; i < plainLen; i++) {
        // Obtaining the ASCII representation
        int decimal = (int)plainText[i];
        // Prediction the starting index to the end index
        endElementIndex = (startElementIndex + remainder + DECIMAL_BIT_STEP - 1) % (2 * DECIMAL_BIT_STEP);
        // Putting a ASCII character into the bit storage;
        // the approach is used by the right-left putting approach
        for (int j = 0; j < DECIMAL_BIT_STEP; j++) {
            int index = (endElementIndex - j) % (2 * DECIMAL_BIT_STEP);
            int rightMostBit = decimal & 1;
            inputBitBuffer[index] = (unsigned char)('0' + rightMostBit); // The bit
            decimal = decimal >> 1; // Right shift a bit
        }
        remainder += DECIMAL_BIT_STEP; // The remainder is equal to the elements which are pushed.

        // Fetch and become the char if the remainder is larger than or equal to UU_BIT_STEP
        for (; remainder >= UU_BIT_STEP;
             startElementIndex = (startElementIndex + UU_BIT_STEP) % (2 * DECIMAL_BIT_STEP), remainder -= UU_BIT_STEP) {

            // 6 bits -> int
            int sixBitsResult = 0;
            for (int j = 0, k = startElementIndex; j < UU_BIT_STEP; j++, k++) {
                k = k % (2 * DECIMAL_BIT_STEP);
                sixBitsResult += ((int)(inputBitBuffer[k] - '0') << (UU_BIT_STEP - j - 1));
            }
            // If the sixBitsResult is equal to 0, the character is char(96), "`".
            encodedText[transIndex++] = (sixBitsResult == 0) ? (unsigned char)(char)96 : (unsigned char)(char)(sixBitsResult + 32);
        }
    }

    // If the remainder is not equal to 0, the last element shall be encoded with 0-bit(s).
    if (remainder != 0) {
        int lastElement = 0; // The value of the last element
        for (int j = 0, k = startElementIndex; j < remainder; j++, k++) {
            k = k % (2 * DECIMAL_BIT_STEP);
            lastElement += ((inputBitBuffer[k] - '0') << (UU_BIT_STEP - j - 1));
        }
        // If the sixBitsResult is equal to 0, the character is char(96), "`".
        encodedText[transIndex++] = (lastElement == 0) ? (unsigned char)(char)96 : (unsigned char)(char)(lastElement + 32);
    }
    encodedText[transIndex] = '\0';
    return 200;
}

/**
 * UUencoded decoder
 *
 * @param oEncoder Encoder* The encoder object
 * @param encodedText unsigned char* The encoded text
 * @param encodedLen int The length of the variable of the encodedText
 * @param plainText unsigned char* The plain text
 * @param plainTextLen int* The length of the plainText; the variable belongs to called-by the value of the address
 * @return
 */
static int UU_Encode_decoder(Encoder* oEncoder,
    const unsigned char* encodedText, int encodedLen, unsigned char* plainText, int* plainTextLen)
{
    const unsigned char* encodedStart = encodedText;
    /*
     * Reserving a character size (6 bit) in advance,
     * and the buffer is modeled as a cyclic storage
     */
    unsigned char inputBitBuffer[(UU_BIT_STEP + UU_BIT_STEP)];
    int totalBits = (encodedLen * UU_BIT_STEP);

    *plainTextLen = totalBits / DECIMAL_BIT_STEP;

    // The length of the array is equal to *encodedLen + 1 (the last element is for the '\0'.)
    plainText[*plainTextLen + 1] = (unsigned char)'\0';

    int startElementIndex = 0; // The index of the starting element
    int endElementIndex = 0; // The index of the last element
    memset(inputBitBuffer, '\0', 2 * UU_BIT_STEP);
    int remainder = 0; // The remainder elements in the stack
    int transIndex = 0; // The index for inputBitBuffer

    for (int i = 0; i < encodedLen; i++) {
        // If the element is equal to the char(96), "`" in six-encoded result, the value is equal to the 0.
        int decimal = ((int)encodedStart[i] == 96) ? 0 : (int)encodedStart[i] - 32;
        // Prediction of the start index to the end index
        endElementIndex = (startElementIndex + remainder + UU_BIT_STEP - 1) % (2 * UU_BIT_STEP);

        // Putting a character into the bit storage
        for (int j = 0; j < UU_BIT_STEP; j++) {
            int index = (endElementIndex - j) % (2 * UU_BIT_STEP);
            int rightMostBit = decimal & 1;
            inputBitBuffer[index] = (unsigned char)('0' + rightMostBit);
            decimal = decimal >> 1; // Shifting a right bit
        }
        remainder += UU_BIT_STEP;

        // For handling bits to eight-encoded process
        for (; remainder >= DECIMAL_BIT_STEP;
             startElementIndex = (startElementIndex + DECIMAL_BIT_STEP) % (2 * UU_BIT_STEP), remainder -= DECIMAL_BIT_STEP) {
            // 6 bits -> int
            int eightBitsResult = 0;
            for (int j = 0, k = startElementIndex; j < DECIMAL_BIT_STEP; j++, k++) {
                k = k % (2 * UU_BIT_STEP);
                eightBitsResult += ((inputBitBuffer[k] - '0') << (DECIMAL_BIT_STEP - j - 1));
            }
            plainText[transIndex++] = (char)eightBitsResult;
        }
    }

    plainText[transIndex] = '\0';
    return 200;
}
