#include "ILogger.h"
#include "JMString.h"
#include "LogManager.h"

using namespace JMLib;


/**
 * @brief ERROR Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * 기본 채널을 생성해놓고, 문자열만으로 로그를 남기고 싶을때 쓴다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_ERROR_D( const wchar_t * ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat );
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList );
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevelForDefaultChannel( NLog::NLevel::DERROR, aOutString );
}

/**
 * @brief TRACE Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * 기본 채널을 생성해놓고, 문자열만으로 로그를 남기고 싶을때 쓴다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_TRACE_D( const wchar_t * ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat );
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList );
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevelForDefaultChannel( NLog::NLevel::DTRACE, aOutString );
}

/**
 * @brief INFO Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * 기본 채널을 생성해놓고, 문자열만으로 로그를 남기고 싶을때 쓴다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_INFO_D( const wchar_t * ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat );
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList );
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevelForDefaultChannel( NLog::NLevel::DINFO, aOutString );
}

/**
 * @brief DEBUG Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * 기본 채널을 생성해놓고, 문자열만으로 로그를 남기고 싶을때 쓴다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_DEBUG_D( const wchar_t * ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat );
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList );
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevelForDefaultChannel( NLog::NLevel::DDEBUG, aOutString );
}

/**
 * @brief DWARN Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * 기본 채널을 생성해놓고, 문자열만으로 로그를 남기고 싶을때 쓴다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_WARN_D( const wchar_t * ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat );
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList );
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevelForDefaultChannel( NLog::NLevel::DWARN, aOutString );
}

/**
 * @brief FATAL Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * 기본 채널을 생성해놓고, 문자열만으로 로그를 남기고 싶을때 쓴다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_FATAL_D( const wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat );
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList );
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevelForDefaultChannel( NLog::NLevel::DFATAL, aOutString );
}



/**
 * @brief ERROR Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_ERROR( const JMLib::NLog::LogChannel & irChannel, const wchar_t * ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevel( irChannel, NLog::NLevel::DERROR, aOutString );
}

/**
 * @brief TRACE Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_TRACE( const JMLib::NLog::LogChannel & irChannel, const wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevel( irChannel, NLog::NLevel::DTRACE, aOutString );
}


/**
 * @brief INFO Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_INFO( const NLog::LogChannel & irChannel, const wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevel( irChannel, NLog::NLevel::DINFO, aOutString );
}

/**
 * @brief DEBUG Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_DEBUG( const NLog::LogChannel & irChannel, const wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevel( irChannel, NLog::NLevel::DDEBUG, aOutString );
}

/**
 * @brief WARN Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_WARN( const NLog::LogChannel & irChannel, const wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevel( irChannel, NLog::NLevel::DWARN, aOutString );
}

/**
 * @brief FATAL Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_FATAL( const NLog::LogChannel & irChannel, const wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & aLM = CLogManager::GetInstance();
    aLM.LogWithLevel( irChannel, NLog::NLevel::DFATAL, aOutString );
}