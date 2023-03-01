#pragma once

#include "ILogger.h"
#include "Lock.h"

using namespace JMLib;

/// @brief 
class CLogManager 
{
private:
    typedef std::map<NLog::LogChannel, slogger> logs;

private:
    static std::unique_ptr<CLogManager> mpInstance;
    static std::once_flag maOnce;
    logs maLogs;
    lock maLock;

public:
    static CLogManager & GetInstance();

    void  RemoveLogger( NLog::LogChannel iaChannel );
    bool SetLogger( NLog::LogChannel iaChannel, NLog::LogType iaType );

    void Log( NLog::LogChannel iaChannel, const string & irString );
    void LogWithLevel( NLog::LogChannel iaChannel, NLog::LevelType iaLevel, const string & irString );

private:
    CLogManager();
    virtual ~CLogManager();
    void SetLogger( NLog::LogChannel iaChannel, slogger ipLogger);
};