#include "Logger.h"

using namespace JMLib;

/**
 * @brief Construct a new JMLib::CLogger::CLogger object
 */
JMLib::CLogger::CLogger(NLog::LevelType iaLevel ) : maLevel( iaLevel )
{
}

/**
 * @brief 초기화 함수 일부 하위클래스에서만 사용한다. 
 * 현재는 아무것도 안함. 
 * @param irString 초기화를 위한 문자열
 * @param iaLevel 표시할 로그 레벨 
 */
void CLogger::Initialize(const string &irString, NLog::LevelType iaLevel )
{
    maLevel = iaLevel;
    return;
}

void CLogger::SetLevel(const NLog::LevelType iaLevel)
{
    maLevel = iaLevel;
}

void CLogger::Log(const string &irString)
{
    LogOut( irString );
}

/**
 * @brief Level에 맞는 coment 를 붙여 로그를 남긴다. 
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
        break;
    case NLog::NLevel::DINFO:
        aLevelString = L"[INFO] ";
        break;
    case NLog::NLevel::DWARN:
        aLevelString = L"[WARN] ";
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
