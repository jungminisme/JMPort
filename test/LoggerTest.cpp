#include <gtest/gtest.h>
#include "LogManager.h"

using namespace JMLib;

TEST( LoggerTest, Initialize )
{
    CLogManager & aLogManager  = CLogManager::GetInstance();

    NLog::LogChannel aChannel = L"test";

    //로거를 등록한다. 
    bool aBoolRet =  aLogManager.AddLogger(aChannel, NLog::NType::DNONE);
    EXPECT_TRUE( aBoolRet );

    // 등록했으면 존재 해야지 
    EXPECT_TRUE( aLogManager.IsExist( aChannel ) );

    // 같은 채널로 또 등록하는 건 안된다. 
    aBoolRet =  aLogManager.AddLogger( aChannel, NLog::NType::DNONE);
    EXPECT_FALSE( aBoolRet );

    NLog::LogChannel aCh2 = L"Test";
    // 채널이름은 대소문자 구문한다. test와 Test 는 다르다. 
    aBoolRet = aLogManager.AddLogger( aCh2 , NLog::NType::DNONE );
    EXPECT_TRUE( aBoolRet );

    //로거를 삭제 한다. 
    aBoolRet = aLogManager.RemoveLogger( aChannel );
    EXPECT_TRUE( aBoolRet );
    // 삭제된 채널은 발견 못해야 한다. 없어야 한다.. 
    aBoolRet = aLogManager.IsExist( aChannel );
    EXPECT_FALSE( aBoolRet );
    // 삭제 안된 채널은 남아 있어야 한다. 
    aBoolRet = aLogManager.IsExist( aCh2 );

    NLog::LogChannel aCh3 = L"common";
    NLog::LogChannel aCh4 = L"library";
    NLog::LogChannel aCh5 = L"blabla";
    NLog::LogChannel aCh6 = L"another";

    // 파일 타입 로그 등록 되어야 한다. 
    aBoolRet = aLogManager.AddLogger( aCh3, NLog::NType::DFILE);
    EXPECT_TRUE( aBoolRet );
    // 콘솔 타입 로거 등록 되어야 한다. 
    aBoolRet = aLogManager.AddLogger( aCh4, NLog::NType::DCONSOLE);
    EXPECT_TRUE( aBoolRet );
    // XML타입 로거는 등록 못한다. 아직 미구현
    aBoolRet =   aLogManager.AddLogger( aCh5, NLog::NType::DXML );
    EXPECT_FALSE( aBoolRet );
    // Network 타입 로거 등록 못한다. 아직 미구현
    aBoolRet = aLogManager.AddLogger( aCh6, NLog::NType::DNETWORK );
    EXPECT_FALSE( aBoolRet );

    aBoolRet = aLogManager.IsExist( aCh4 );
    EXPECT_TRUE( aBoolRet );
    aBoolRet = aLogManager.RemoveLogger( aCh4 );
    EXPECT_TRUE( aBoolRet );

    // 다음 테스트를 위해 로그매니저를 정리 한다. 
    // 모든 로거를 다 삭제 한다. 
    aLogManager.Finalize();
    // 확인했을때 로거들이 존재한다고 나오면 안됨. 
    EXPECT_FALSE( aLogManager.IsExist( aChannel ));
    EXPECT_FALSE( aLogManager.IsExist( aCh2 ));
    EXPECT_FALSE( aLogManager.IsExist( aCh3 ));
    EXPECT_FALSE( aLogManager.IsExist( aCh4 ));
    EXPECT_FALSE( aLogManager.IsExist( aCh5 ));
    EXPECT_FALSE( aLogManager.IsExist( aCh6 ));
}

TEST( LoggerTest, ConsoleLogger )
{
    CLogManager & aLM = CLogManager::GetInstance();
    string aCh1 = L"LoggerTest";
    EXPECT_TRUE( aLM.AddLogger( aCh1, NLog::NType::DCONSOLE ) );

    string aString1( L"This is First String ");
    string aString2( L"이것은 한글 ");
    aLM.Log( aCh1, aString1 );
    aLM.Log( aCh1, aString2 );

    LOG_DEBUG( aCh1, L"This is First Log String" );
    LOG_ERROR( aCh1, L"이것은 첫번째 한글 로그" );

    aLM.Finalize();
    EXPECT_FALSE( aLM.IsExist(aCh1) );
}

TEST(LoggerTest, FileLogger )
{

    CLogManager & aLM = CLogManager::GetInstance();
    string aCh1 = L"LoggerTest";
    EXPECT_TRUE( aLM.AddLogger( aCh1, NLog::NType::DCONSOLE ) );

    aLM.Finalize();
    EXPECT_FALSE( aLM.IsExist(aCh1) );
}

TEST( LoggerTest, NonLogger )
{

    CLogManager & aLM = CLogManager::GetInstance();
    string aCh1 = L"LoggerTest";
    EXPECT_TRUE( aLM.AddLogger( aCh1, NLog::NType::DCONSOLE ) );

    aLM.Finalize();
    EXPECT_FALSE( aLM.IsExist(aCh1) );
}

TEST( LoggerTest, DefaultChannel )
{
    CLogManager & aLM = CLogManager::GetInstance();
    string aCh1 = L"LoggerTest";
    EXPECT_TRUE( aLM.AddLogger( aCh1, NLog::NType::DCONSOLE ) );

    // default 를 LoggerTest 로 하고 테스트 해본다. 
    aLM.SetDefaultChannel( aCh1 );
    // default 를 Test 로 하고 해본다. 이건 동작 안해야 한다. 
}