#include "Logger.h"

using namespace JMLib;
void CLogger::Log( const string & irString )
{

}

/**
 * @brief Level에 맞는 cooment 를 붙여 로그를 남긴다. 
 * 입력된 레벨이 현재 로거의 로그 레벨보다 작으면 남기지 않는다. 
 * @param iaLevel 로그의 등급 
 * @param irString 로그 내용
 */
void CLogger::LogWithLevel( const NLog::LevelType iaLevel, const string & irString )
{
    lockguard aLG(maLock);
    if( iaLevel < maLevel )
        return;
    string aOutString;
    string aLevelString;

    switch (iaLevel)
    {
    case NLog::NLevel::DDEBUG:
        aLevelString = L"[DEBUG] ";
\        break;
    case NLog::NLevel::DINFO:
        aLevelString = L"[INFO] ";
        break;
    case NLog::NLevel::DWARN:
        aLevelString = L"[INFO] ";
        break;
    case NLog::NLevel::DERROR :
        aLevelString = L"[ERROR] ";
        break;
    case NLog::NLevel::DFATAL :
        aLevelString = L"[FATAL] ";
        break;
    case NLog::NLevel::DTRACE:
        aLevelString = L"[TRACE] ";
        break;
    default:
        return;
    }

    aOutString = aLevelString + irString;
    LogOut( aOutString );
}

/// @brief 디버그를 위하여 파일명과 라인을 남기는 로그
/// @param irSrcFile 로그가 남겨진 소스파일
/// @param iaLine 로그가 있는 라인
/// @param iaLevel 로그의 등급
/// @param irLogString  로그 내용
void CLogger::LogWithAllArg( const string & irSrcFile, const uint32 iaLine, 
        const NLog::LevelType iaLevel, const string & irLogString )
{
    string aString;
    aString.Format( L"(%s, %d ) %s ", irSrcFile.c_str(), iaLine, irLogString );

    LogWithLevel( iaLevel, aString );
}
