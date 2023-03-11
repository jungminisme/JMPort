#include <gtest/gtest.h>

#include <filesystem>
#include "JMFile.h"
using namespace JMLib;

TEST(FileTest, Open )
{

    CFile aFile;
    string aFileName( L"TestFile.txt");
//    std::filesystem::remove( "TestFile.txt" );
    EXPECT_FALSE( aFile.IsOpen() ); // 이름없이 생성했는데 파일이 열려 있으면 안된다. 

    aFile.Open( aFileName, NFile::NMode::DWRITE );
    EXPECT_TRUE( aFile.IsOpen() );

    aFile.Close();
    EXPECT_FALSE( aFile.IsOpen() );  // 닫았는데 열려있으면안된다. 

    CFile aSam2( aFileName, NFile::NMode::DWRITE );
    EXPECT_TRUE( aSam2.IsOpen() );      // 이름주고 생성했으면 열려있어야 한다. 
    NFile::mode aMode = NFile::NMode::DWRITE;
    EXPECT_FALSE( aSam2.Open(aFileName.c_str(), aMode) ); // 열려 잇는데 또 열면 실패 
    EXPECT_TRUE( aSam2.IsOpen() );  // 원래 열려 있던 파일 계속 유지 
    aSam2.Close();

    EXPECT_TRUE( aSam2.Open( aFileName.c_str(), NFile::NMode::DWRITE ) );
    aSam2.Close();

    CFile aSam3( aFileName.c_str(), NFile::NMode::DWRITE );
    EXPECT_TRUE( aSam3.IsOpen() );
    aSam3.Close();
}

TEST( FileTest, Write )
{
    string aLine1 = L"동해물과 백두산이 마르고 닳도록";
    string aLine2 = L"하느님이 보우하사 우리나라 만세" ;
    string aLine3 = L"무궁화 삼천리 화려강산 ";
    string aLine4 = L"대한사람 대한으로 길이보전하세";
    CFile aFile;
    string aFileName( L"TestFile.txt");
    aFile.Open( aFileName, NFile::NMode::DWRITE );
    aFile << aLine1;
    EXPECT_TRUE( aFile.IsOpen() );
    EXPECT_EQ( aFile.Size(), aLine1.Size() );
    aFile << aLine2 << aLine3;
    EXPECT_EQ( aFile.Size(), ( aLine1.Size() + aLine2.Size() + aLine3.Size() ) );
    aFile.AppendNewLine();
    EXPECT_EQ( aFile.Size(), ( aLine1.Size() + aLine2.Size() + aLine3.Size() + 1 ) );
    aFile << aLine4.c_str();
    aFile.AppendLine( aLine1 );
    aFile.Close();
}