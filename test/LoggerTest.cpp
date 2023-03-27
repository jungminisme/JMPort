#include <gtest/gtest.h>
#include "LogManager.h"
#include "JMFile.h"

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

    remove("common.log");
}

TEST( LoggerTest, ConsoleLogger )
{
    CLogManager & aLM = CLogManager::GetInstance();
    string aCh1 = L"LoggerTest";
    EXPECT_TRUE( aLM.AddLogger( aCh1, NLog::NType::DCONSOLE ) );

    string aLog1 = L"Error Log ";
    string aLog2 = L"Trace Log ";
    string aLog3 = L"Info Log ";
    string aLog4 = L"Debug Log ";
    string aLog5 = L"Warning Log ";

    //! Level 없이 Log 출력
    aLM.Log( aCh1, aLog1 );
    aLM.Log( aCh1, aLog2 );
    aLM.Log( aCh1, aLog3 );
    aLM.Log( aCh1, aLog4 );
    aLM.Log( aCh1, aLog5 );

    //! 레벨에 맞는 Log 출력
    aLM.LogWithLevel( aCh1, NLog::NLevel::DERROR, aLog1 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DTRACE, aLog2 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DINFO, aLog3 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DDEBUG, aLog4 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DWARN, aLog5 );

    //! 로그 매니저를 통하지 않는 로그 출력 함수 직접 호출
    LOG_ERROR( aCh1, L"LogString is %S", aLog1.c_str() );
    LOG_TRACE( aCh1, L"LogString is %S", aLog2.c_str() );
    LOG_INFO( aCh1, L"LogString is %S", aLog3.c_str() );
    LOG_DEBUG( aCh1, L"LogString is %S", aLog4.c_str() );
    LOG_WARN( aCh1, L"LogString is %S", aLog5.c_str() );

    //! 잘못된 채널에 로그 남길때 테스트 
    string aCh2 = L"Channel2";
    string aLogCh2 = L"Channel2 Log Message! This must not print to console!!";
    aLM.Log( aCh2, aLogCh2 );
    aLM.LogWithLevel( aCh2, NLog::NLevel::DERROR, aLogCh2 );
    LOG_ERROR( aCh2, L"LogString is %S, %S", aLogCh2.c_str(), aLog1.c_str() );
    LOG_TRACE( aCh2, L"LogString is %S, %S", aLogCh2.c_str(), aLog2.c_str() );
    LOG_INFO( aCh2, L"LogString is %S, %S", aLogCh2.c_str(), aLog3.c_str() );
    LOG_DEBUG( aCh2, L"LogString is %S, %S", aLogCh2.c_str(), aLog4.c_str() );
    LOG_WARN( aCh2, L"LogString is %S, %S", aLogCh2.c_str(), aLog5.c_str() );

    aLM.Finalize();
    EXPECT_FALSE( aLM.IsExist(aCh1) );
}

TEST(LoggerTest, FileLogger )
{

    CLogManager & aLM = CLogManager::GetInstance();
    string aCh1 = L"LoggerTest";
    EXPECT_TRUE( aLM.AddLogger( aCh1, NLog::NType::DFILE ) );

    string aLog1 = L"Error Log ";
    string aLog2 = L"Trace Log ";
    string aLog3 = L"Info Log ";
    string aLog4 = L"Debug Log ";
    string aLog5 = L"Warning Log ";

    //! Level 없이 Log 출력
    aLM.Log( aCh1, aLog1 );
    aLM.Log( aCh1, aLog2 );
    aLM.Log( aCh1, aLog3 );
    aLM.Log( aCh1, aLog4 );
    aLM.Log( aCh1, aLog5 );

    //! 레벨에 맞는 Log 출력
    aLM.LogWithLevel( aCh1, NLog::NLevel::DERROR, aLog1 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DTRACE, aLog2 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DINFO, aLog3 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DDEBUG, aLog4 );
    aLM.LogWithLevel( aCh1, NLog::NLevel::DWARN, aLog5 );

    //! 로그 매니저를 통하지 않는 로그 출력 함수 직접 호출
    LOG_ERROR( aCh1, L"LogString is %S", aLog1.c_str() );
    LOG_TRACE( aCh1, L"LogString is %S", aLog2.c_str() );
    LOG_INFO( aCh1, L"LogString is %S", aLog3.c_str() );
    LOG_DEBUG( aCh1, L"LogString is %S", aLog4.c_str() );
    LOG_WARN( aCh1, L"LogString is %S", aLog5.c_str() );

    //! 로거를 삭제 한다. 그럼 File또한 Close 되어야 한다. 
    aLM.RemoveLogger( aCh1 );

    //! File을 열어 내용을 확인한다. 
    string aFileName = aCh1;
    aFileName << L".log";
    JMLib::CFile aFile( aFileName, NFile::NMode::DREAD );
    EXPECT_TRUE( aFile.IsOpen() );

    //! 파일에서 15줄 읽는다. 
    string aReadLine[15];
    for( int i = 0; i < 15; i++ )
    {
        aFile >> aReadLine[i];
    }
    aFile.Close();

    //! 읽은 각 줄의 내용은 아래와 같아야 한다. 
    EXPECT_STREQ( aReadLine[0].c_str(), L"[DEBUG] Error Log ");
    EXPECT_STREQ( aReadLine[1].c_str(), L"[DEBUG] Trace Log ");
    EXPECT_STREQ( aReadLine[2].c_str(), L"[DEBUG] Info Log ");
    EXPECT_STREQ( aReadLine[3].c_str(), L"[DEBUG] Debug Log ");
    EXPECT_STREQ( aReadLine[4].c_str(), L"[DEBUG] Warning Log ");

    EXPECT_STREQ( aReadLine[5].c_str(), L"[ERROR] Error Log ");
    EXPECT_STREQ( aReadLine[6].c_str(), L"[TRACE] Trace Log ");
    EXPECT_STREQ( aReadLine[7].c_str(), L"[INFO] Info Log ");
    EXPECT_STREQ( aReadLine[8].c_str(), L"[DEBUG] Debug Log ");
    EXPECT_STREQ( aReadLine[9].c_str(), L"[WARN] Warning Log ");

    EXPECT_STREQ( aReadLine[10].c_str(), L"[ERROR] LogString is Error Log ");
    EXPECT_STREQ( aReadLine[11].c_str(), L"[TRACE] LogString is Trace Log ");
    EXPECT_STREQ( aReadLine[12].c_str(), L"[INFO] LogString is Info Log ");
    EXPECT_STREQ( aReadLine[13].c_str(), L"[DEBUG] LogString is Debug Log ");
    EXPECT_STREQ( aReadLine[14].c_str(), L"[WARN] LogString is Warning Log ");

    aLM.Finalize();
    EXPECT_FALSE( aLM.IsExist(aCh1) );

    //! 모든 테스트가 끝난후 로그 파일을 삭제 한다. 
    remove("LoggerTest.log");
}

TEST( LoggerTest, NonLogger )
{

    CLogManager & aLM = CLogManager::GetInstance();
    string aCh1 = L"LoggerTest";
    EXPECT_TRUE( aLM.AddLogger( aCh1, NLog::NType::DNONE ) );

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