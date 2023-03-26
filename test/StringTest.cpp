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

TEST(StringTest, MiscTest)
{
    JMLib::string aSam1( L"Lonely Night");
    JMLib::string aSam2( L"Puff" );
    JMLib::string aSam3( aSam1 );

    //Compare Test
    EXPECT_NE( aSam1.Compare(aSam2), 0 );
    EXPECT_EQ( aSam1.Compare(aSam3), 0 );

    EXPECT_FALSE( aSam1 == aSam2 );
    EXPECT_TRUE( aSam1 == aSam3 );

    // != Test
    EXPECT_TRUE( aSam1 != aSam2 );
    EXPECT_FALSE( aSam1 != aSam3 );

    //Empty Test
    JMLib::string aSam4;
    EXPECT_TRUE( aSam4.IsEmpty() );
    EXPECT_FALSE( aSam2.IsEmpty() );

    //Size Test
    EXPECT_EQ( aSam4.Size(), 0 );
    EXPECT_EQ( aSam2.Size(), 4 );

    //Clear Test
    aSam2.Clear();
    EXPECT_EQ( aSam2.Size(), 0 );
    EXPECT_STREQ( aSam2.c_str(), L"" );

    JMLib::string aSam5( L"a" );
    JMLib::string aSam6(L"b");
    JMLib::string aSam7(L"ab");

    // 부등호는 Dictionary order 를 따른다.  
    EXPECT_TRUE( aSam5 < aSam6 );
    EXPECT_TRUE( aSam5 < aSam7 );
    EXPECT_FALSE( aSam6 < aSam7 );
    EXPECT_FALSE( aSam5 < aSam5 );
    EXPECT_TRUE( aSam2 < aSam5);

    JMLib::string aSam8( L"  Whole new world   !   " );
    JMLib::string aSam9( aSam8 );

    EXPECT_TRUE( aSam8 == aSam9 );
    aSam9.Trim();
    EXPECT_TRUE( aSam8.Size() > aSam9.Size() );
    EXPECT_STREQ( aSam9.c_str(), L"Whole new world   !" );

    JMLib::string aSam10( L"213456");
    EXPECT_EQ( aSam10.ToInt(), 213456 );
    aSam10 = L"2145t345";
    EXPECT_NE( aSam10.ToInt(), 2145345 );

    JMLib::string aSam11( L"3.141592");
    EXPECT_EQ( aSam11.ToFloat(), 3.141592 );


    JMLib::string aSam12;
    JMLib::string aTestString( L"Format Test");
    //! string 출력시 %s 와 %S 는 많이 다르다. UNICODE는 %S만 쓴다. 
    aSam12.Format(L"This is %S No. %d ", aTestString.c_str(), 1);
    EXPECT_STREQ( aSam12.c_str(), L"This is Format Test No. 1 " );

    JMLib::string aSam13;
    aSam13.Format( L"여기에 그냥 나열을 해요 다른 파라미터 없어요. ");
}