#include <gtest/gtest.h>

#include "JMString.h"

TEST(StringTest, Constructor)
{
    JMLib::string aSam1;
    EXPECT_STREQ(aSam1.c_str(), L"" );
    JMLib::string aString(L"Hello");
    EXPECT_STREQ( aString.c_str(), L"Hello" );

    JMLib::string aSam2(aString);
    EXPECT_STREQ( aSam2.c_str(), L"Hello" );
}

TEST(StringTest, Assign)
{
    JMLib::string aSam1;
    aSam1 = L" World" ;
    EXPECT_STREQ( aSam1.c_str(), L" World" );
    JMLib::string aSam2;
    aSam2.Assign( aSam1 );
    EXPECT_STREQ( aSam2.c_str(), L" World" );

    JMLib::string aSam3;
    aSam3 = aSam1;
    EXPECT_STREQ( aSam3.c_str(), L" World" );

    JMLib::string aSam4;
    aSam4 = L" World";
    EXPECT_STREQ( aSam4.c_str(), L" World" );

    JMLib::string aSam5 = L" World";
    EXPECT_STREQ( aSam5.c_str(), L" World" );

    JMLib::string aSam6 = aSam5;
    EXPECT_STREQ( aSam6.c_str(), L" World" );
}