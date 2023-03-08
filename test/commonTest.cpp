#include <gtest/gtest.h>

#include "JMString.h"

TEST(StringTest, Constructor)
{
    // 빈생성자
    JMLib::string aSam1;
    EXPECT_STREQ(aSam1.c_str(), L"" );

    // wchar_t 생성자
    JMLib::string aString(L"Hello");
    EXPECT_STREQ( aString.c_str(), L"Hello" );

    // JMLib::string 생성자
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

    aSam6.Clear();
    EXPECT_STREQ( aSam6.c_str(), L"" );
}

TEST(StringTest, Append )
{
    JMLib::string aSam1( L"My Name is ");
    JMLib::string aSam2;
    //Append with << string 
    aSam2 << aSam1;
    EXPECT_STREQ( aSam2.c_str(), L"My Name is ");
    JMLib::string aSam3;
    //Append with << wchar_t 
    aSam3 << L"Gilbert Grape";
    EXPECT_STREQ( aSam3.c_str(), L"Gilbert Grape" );
    // Append with operator +
    JMLib::string aSam4 = aSam2 + aSam3;

    EXPECT_STREQ( aSam4.c_str(), L"My Name is Gilbert Grape");
    // 주의 한다. 수식과는 다르다. 
    EXPECT_STREQ( aSam2.c_str(), L"My Name is Gilbert Grape");

    // 아래 append 는 안된다. 
    // aSam4 = L"My Name is " + aSam3;

    // 이건 된다. 
    aSam4.Clear();
    aSam2 = aSam1;
    aSam4 = aSam2 + L"Gilbert Grape";
    EXPECT_STREQ( aSam4.c_str(), L"My Name is Gilbert Grape");
    EXPECT_STREQ( aSam2.c_str(), L"My Name is Gilbert Grape");

    aSam4.Clear();
    aSam2 = aSam1;
    // Append with << string tow times;
    aSam4 << aSam2 << aSam3; 
    EXPECT_STREQ( aSam4.c_str(), L"My Name is Gilbert Grape");
    EXPECT_STREQ( aSam2.c_str(), aSam1.c_str() );
    EXPECT_STREQ( aSam3.c_str(), L"Gilbert Grape" );

    // Append with << wchar_t tow times;
    aSam4.Clear();
    aSam4 << L"My Name is " << L"Gilbert Grape";
    EXPECT_STREQ( aSam4.c_str(), L"My Name is Gilbert Grape");

    // Append with << string << wchar_t 
    aSam4.Clear();
    aSam4 << aSam2 << L"Gilbert Grape";
    EXPECT_STREQ( aSam4.c_str(), L"My Name is Gilbert Grape");

    // Append with << wchar_t << string 
    aSam4.Clear();
    aSam4 << L"My Name is " << aSam3;
    EXPECT_STREQ( aSam4.c_str(), L"My Name is Gilbert Grape");

}