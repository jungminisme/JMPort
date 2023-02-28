#pragma once

#include "ILogger.h"
#include "Lock.h"

using namespace JMLib;

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

    void SetLogger( NLog::LogChannel iaChannel, slogger ipLogger);
    void RemoveLogger( NLog::LogChannel iaChannel );

    void Log( NLog::LogChannel iaChannel, const string & irString );
    void LogWithLevel( NLog::LogChannel iaChannel, NLog::LevelType iaLevel, const string & irString );

private:
    CLogManager();
    virtual ~CLogManager();
};