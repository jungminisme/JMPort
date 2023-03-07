#include <gtest/gtest.h>

#include "JMString.h"

TEST(CommonTest, StringTest)
{
    JMLib::string aString(L"Hello");
    EXPECT_STREQ( aString.c_str(), L"Hello" );
    aString << L" World" ;
    EXPECT_STREQ( aString.c_str(), L"Hello World" );
    EXPECT_EQ( aString.Size(), 11 );

}