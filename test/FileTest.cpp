#include <gtest/gtest.h>

#include "JMFile.h"
using namespace JMLib;

TEST(FileTest, Open )
{

    CFile aFile;
    EXPECT_FALSE( aFile.IsOpen() ); // 이름없이 생성했는데 파일이 열려 있으면 안된다. 

    aFile.Open( string(L"TestFile.txt"), NFile::NMode::DREAD_WRITE );
    EXPECT_TRUE( aFile.IsOpen() );

    aFile.Close();
    EXPECT_FALSE( aFile.IsOpen() );  // 닫았는데 열려있으면안된다. 

    CFile aSam2( string(L"TestFile.txt"), NFile::NMode::DWRITE );
    NFile::mode aMode = NFile::NMode::DREAD_WRITE;
    EXPECT_FALSE( aFile.Open(L"TestFile.txt", aMode) );
    EXPECT_TRUE( aFile.IsOpen() );
    aSam2.Close();

    /*
        CFile();
    ~CFile();
    bool Open( const string & irFileName, NFile::mode iaMode );
    int32 Append( const string & irString );

    int32 ReadLine( string & orString );

    bool IsOpen() const;

    CFile & operator << ( const string & irString );
    CFile & operator >> ( string & orString );

    int32 Size();


    void Close();
    */
}