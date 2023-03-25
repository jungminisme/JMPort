#include <gtest/gtest.h>
#include <stdio.h>

#include "JMFile.h"
#include "ConsoleLogger.h"

using namespace JMLib;

static JMLib::CConsoleLogger gLogger;

TEST(FileTest, Open )
{

    remove( "TestFile.txt");
    CFile aFile;
    string aFileName( L"TestFile.txt");
    EXPECT_FALSE( aFile.IsOpen() ); // 이름없이 생성했는데 파일이 열려 있으면 안된다. 
    
    gLogger.LogOut( JMLib::string( "TestFile Name is ") + aFileName );

    aFile.Open( aFileName, NFile::NMode::DWRITE );
    EXPECT_TRUE( aFile.IsOpen() );

    aFile.Close();
    EXPECT_FALSE( aFile.IsOpen() );  // 닫았는데 열려있으면안된다. 

    CFile aSam2( aFileName, NFile::NMode::DWRITE );
    EXPECT_TRUE( aSam2.IsOpen() );      // 이름주고 생성했으면 열려있어야 한다. 
    NFile::mode aMode = NFile::NMode::DWRITE;
    EXPECT_FALSE( aSam2.Open(aFileName.c_str(), aMode) ); // 열려 있는데 또 열면 실패 
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
    int32 aRet = aFile.Append( aLine1 );
    EXPECT_GT( aRet, 0 );
    aFile << aLine1;
    EXPECT_TRUE( aFile.IsOpen() );
    EXPECT_GT( aFile.Size(), aRet );
    aFile << aLine2 << aLine3;
    aRet += ( aLine2.Size() + aLine3.Size() );
    EXPECT_GT( aFile.Size(), aRet );
    aFile.AppendNewLine();
    EXPECT_GT( aFile.Size(), aRet + 1 );
    aFile << aLine4.c_str();
    aFile.AppendLine( aLine1 );
    aFile.Close();
}

TEST(FileTest, Read )
{
    string aStr1;
    EXPECT_EQ( aStr1.Size(), 0 );
    CFile aReadFile( L"TestFile.txt",NFile::NMode::DWRITE );
    // ReadFile이 WriteMode로 열렸다. 읽히면 안됨. 
    EXPECT_LE( aReadFile.ReadLine(aStr1), 0 );
    EXPECT_TRUE( aReadFile.IsOpen() );
    aReadFile.Close();

    aReadFile.Open( L"TestFile.txt",NFile::NMode::DREAD );
    EXPECT_TRUE( aReadFile.IsOpen() );
    EXPECT_GT( aReadFile.ReadLine( aStr1 ), 0 );
    EXPECT_GT( aStr1.Size(), 0 );
    string aStr2, aStr3;
    aReadFile >> aStr2 >> aStr3;
    EXPECT_GT( aStr2.Size(), 0 );
    EXPECT_GT( aStr3.Size(), 0 );
    string aStr4, aStr5, aStr6;
    aReadFile >> aStr4 >> aStr5 >> aStr6;
    EXPECT_GT( aStr4.Size(), 0 );
    EXPECT_GT( aStr5.Size(), 0 );
    EXPECT_GT( aStr6.Size(), 0 );
}