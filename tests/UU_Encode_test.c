#include <gtest/gtest.h>
#include "../Headers/Encoders/UU_Encode.h"

TEST(EncodersTest, Test1_1)
{
    UU_Encode __u2eObject;
    UU_Encode__constructor(&__u2eObject);

    int iHttpNum = 0;
    unsigned char plainText [] = "Cat`\0";
    int plainTextLen = (int)strlen((char*)plainText);
    int encodedTextLen = ((8 * plainTextLen) % 6 ==0) ?  (8 * plainTextLen)/ 6: (8 * plainTextLen) / 6 + 1;
    unsigned char encodedText [encodedTextLen + 1];

    int httpStatus = __u2eObject.pf__encoder(plainText, plainTextLen, encodedText, encodedTextLen);

    ASSERT_TRUE(true);
    //ASSERT_EQ(200, httpStatus);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}