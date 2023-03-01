#include "LogManager.h"


CLogManager & CLogManager::GetInstance()
{
    std::call_once( CLogManager::maOnce, []() 
    {
        mpInstance.reset( new CLogManager());
    });
    return * mpInstance;
}

bool CLogManager::SetLogger( NLog::LogChannel iaChannel, NLog::LogType iaType )
{
    lockguard aLG(maLock );
    logs::iterator it = maLogs.find( iaChannel );
    if( it != maLogs.end())
        return false;
    slogger aLogger;
    switch( iaType )
    {
        case NLog::NType::DNONE:
            aLogger = std::make_shared<CNonLogger>(iaChannel);
        break;
        case NLog::NType::DFILE:
        break;
        case NLog::NType::DXML:
        break;
        case NLog::NType::DCONSOLE:
        break;
        default:
            return false;
    }

    return true;
}

void CLogManager::SetLogger( NLog::LogChannel iaChannel, slogger ipLogger)
{
    lockguard aLG( maLock );
    maLogs.insert(logs::value_type(iaChannel, ipLogger));
}

void CLogManager::RemoveLogger( NLog::LogChannel iaChannel )
{
    lockguard aLG( maLock );
    logs::iterator aIt = maLogs.find( iaChannel );
    if( aIt == maLogs.end() )
        return;
    slogger aLog = aIt->second;
    aLog->Finalize();
    maLogs.erase(aIt);
}

void CLogManager::Log( NLog::LogChannel iaChannel, const string & irString )
{
    LogWithLevel( iaChannel, NLog::NLevel::DDEBUG, irString );
}

void CLogManager::LogWithLevel( NLog::LogChannel iaChannel, NLog::LevelType iaLevel, const string & irString )
{
    lockguard aLG( maLock );
    logs::iterator it = maLogs.find(iaChannel );
    if( it == maLogs.end() )
        return;
    slogger aLog = it->second;
    aLog->LogWithLevel( iaLevel, irString );
}

CLogManager::CLogManager()
{
}

CLogManager::~CLogManager()
{
}