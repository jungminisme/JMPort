#include "ILogger.h"
#include "JMString.h"
#include "LogManager.h"

using namespace JMLib;


/**
 * @brief ERROR Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_ERROR( const uint16 iaChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & pLM = CLogManager::GetInstance();

    pLM.LogWithLevel( iaChannel, NLog::NLevel::DERROR, aOutString );
}

/**
 * @brief TRACE Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_TRACE( const uint16 iaChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & pLM = CLogManager::GetInstance();

    pLM.LogWithLevel( iaChannel, NLog::NLevel::DTRACE, aOutString );
}


/**
 * @brief INFO Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_INFO( const uint16 iaChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & pLM = CLogManager::GetInstance();

    pLM.LogWithLevel( iaChannel, NLog::NLevel::DINFO, aOutString );
}

/**
 * @brief DEBUG Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_DEBUG( const uint16 iaChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & pLM = CLogManager::GetInstance();

    pLM.LogWithLevel( iaChannel, NLog::NLevel::DDEBUG, aOutString );
}

/**
 * @brief WARN Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param iaChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_WARN( const uint16 iaChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager & pLM = CLogManager::GetInstance();

    pLM.LogWithLevel( iaChannel, NLog::NLevel::DWARN, aOutString );
}

