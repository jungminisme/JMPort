#pragma once

#include "ILogger.h"
#include "Lock.h"

using namespace JMLib;

/**
 * @brief Log에 관한 모든 것을 총괄하는 클래스
 * 채널을 관리하고, 로그를 전역적으로 출력한다. 
 */
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

    void  RemoveLogger( const NLog::LogChannel & irChannel );
    bool SetLogger( const NLog::LogChannel & irChannel, NLog::LogType iaType );

    void Log( const NLog::LogChannel & irChannel, const string & irString );
    void LogWithLevel( const NLog::LogChannel & irChannel, NLog::LevelType iaLevel, const string & irString );
    void LogWithAllArg( const NLog::LogChannel & irChannel, string & irSrcFile, const uint32 iaLine, 
        const NLog::LevelType iaLevel, const string & irLogString );

private:
    CLogManager();
    virtual ~CLogManager();
};