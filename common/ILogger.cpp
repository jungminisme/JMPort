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
void LOG_ERROR(wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat );
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList );
    CLogManager * pLM =CLogManager::GetInstance();
    pLM->LogWithLevel();
}


void LOG_ERROR(const JMLib::NLog::LogChannel &irChannel, wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();

    pLM->LogWithLevel( irChannel, NLog::NLevel::DERROR, aOutString );
}

/**
 * @brief TRACE Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_TRACE( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();

    pLM->LogWithLevel( irChannel, NLog::NLevel::DTRACE, aOutString );
}


/**
 * @brief INFO Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_INFO( const NLog::LogChannel & irChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();

    pLM->LogWithLevel( irChannel, NLog::NLevel::DINFO, aOutString );
}

/**
 * @brief DEBUG Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_DEBUG( const NLog::LogChannel & irChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();

    pLM->LogWithLevel( irChannel, NLog::NLevel::DDEBUG, aOutString );
}

/**
 * @brief WARN Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_WARN( const NLog::LogChannel & irChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();

    pLM->LogWithLevel( irChannel, NLog::NLevel::DWARN, aOutString );
}

/**
 * @brief FATAL Log 를 위한 함수
 * 항상 Log 객체를 생성해서 로그를 남기는 것은 코드 낭비가 많이 일반 함수로 로그를 남기게 해준다. 
 * @param irChannel 생성된로그의 채널
 * @param ipFormat 로그 포멧, printf 의 포멧으로 출력한다. 
 * @param ...  포멧을 위한 추가 파라미터
 */
void LOG_FATAL( const NLog::LogChannel & irChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();

    pLM->LogWithLevel( irChannel, NLog::NLevel::DFATAL, aOutString );
}

/**
 * @brief ERROR 로그를 위한 함수중 많은 파라미터용
 *  파일 이름과 라인을 포함한 좀더 많은 정보용 함수이다. 
 * @param irChannel 생성된 로그의 채널
 * @param ipFileName 로그가 작성된 파일 
 * @param iaLine 로그가 작성된 라인
 * @param ipFormat  로그 포멧, printf 의 포멧으로 출력
 * @param ... 포멧을 위한 추가 파라미터
 */
void LOG_ERROR(const NLog::LogChannel &irChannel, wchar_t *ipFileName, int32 iaLine, wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();
    string aFileName( ipFileName);
    pLM->LogWithAllArg( irChannel, aFileName, iaLine, NLog::NLevel::DERROR, aOutString );
}

/**
 * @brief TRACE 로그를 위한 함수중 많은 파라미터용
 *  파일 이름과 라인을 포함한 좀더 많은 정보용 함수이다. 
 * @param irChannel 생성된 로그의 채널
 * @param ipFileName 로그가 작성된 파일 
 * @param iaLine 로그가 작성된 라인
 * @param ipFormat  로그 포멧, printf 의 포멧으로 출력
 * @param ... 포멧을 위한 추가 파라미터
 */
void LOG_TRACE(const NLog::LogChannel &irChannel, wchar_t *ipFileName, int32 iaLine, wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();
    string aFileName( ipFileName);
    pLM->LogWithAllArg( irChannel, aFileName, iaLine, NLog::NLevel::DTRACE, aOutString );
}

/**
 * @brief INFO 로그를 위한 함수중 많은 파라미터용
 *  파일 이름과 라인을 포함한 좀더 많은 정보용 함수이다. 
 * @param irChannel 생성된 로그의 채널
 * @param ipFileName 로그가 작성된 파일 
 * @param iaLine 로그가 작성된 라인
 * @param ipFormat  로그 포멧, printf 의 포멧으로 출력
 * @param ... 포멧을 위한 추가 파라미터
 */
void LOG_INFO(const NLog::LogChannel &irChannel, wchar_t *ipFileName, int32 iaLine, wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();
    string aFileName( ipFileName);
    pLM->LogWithAllArg( irChannel, aFileName, iaLine, NLog::NLevel::DINFO, aOutString );
}

/**
 * @brief DEBUG 로그를 위한 함수중 많은 파라미터용
 *  파일 이름과 라인을 포함한 좀더 많은 정보용 함수이다. 
 * @param irChannel 생성된 로그의 채널
 * @param ipFileName 로그가 작성된 파일 
 * @param iaLine 로그가 작성된 라인
 * @param ipFormat  로그 포멧, printf 의 포멧으로 출력
 * @param ... 포멧을 위한 추가 파라미터
 */
void LOG_DEBUG(const NLog::LogChannel &irChannel, wchar_t *ipFileName, int32 iaLine, wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();
    string aFileName( ipFileName);
    pLM->LogWithAllArg( irChannel, aFileName, iaLine, NLog::NLevel::DDEBUG, aOutString );
}

/**
 * @brief WARN 로그를 위한 함수중 많은 파라미터용
 *  파일 이름과 라인을 포함한 좀더 많은 정보용 함수이다. 
 * @param irChannel 생성된 로그의 채널
 * @param ipFileName 로그가 작성된 파일 
 * @param iaLine 로그가 작성된 라인
 * @param ipFormat  로그 포멧, printf 의 포멧으로 출력
 * @param ... 포멧을 위한 추가 파라미터
 */
void LOG_WARN(const NLog::LogChannel &irChannel, wchar_t *ipFileName, int32 iaLine, wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();
    string aFileName( ipFileName);
    pLM->LogWithAllArg( irChannel, aFileName, iaLine, NLog::NLevel::DWARN, aOutString );
}

/**
 * @brief FATAL 로그를 위한 함수중 많은 파라미터용
 *  파일 이름과 라인을 포함한 좀더 많은 정보용 함수이다. 
 * @param irChannel 생성된 로그의 채널
 * @param ipFileName 로그가 작성된 파일 
 * @param iaLine 로그가 작성된 라인
 * @param ipFormat  로그 포멧, printf 의 포멧으로 출력
 * @param ... 포멧을 위한 추가 파라미터
 */
void LOG_FATAL(const NLog::LogChannel &irChannel, wchar_t *ipFileName, int32 iaLine, wchar_t *ipFormat, ...)
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);

    CLogManager * pLM = CLogManager::GetInstance();
    string aFileName( ipFileName);
    pLM->LogWithAllArg( irChannel, aFileName, iaLine, NLog::NLevel::DFATAL, aOutString );
}
