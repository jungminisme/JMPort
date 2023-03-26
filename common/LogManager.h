#pragma once

#include "ILogger.h"
#include "Lock.h"


namespace JMLib 
{
    /**
     * @brief Log에 관한 모든 것을 총괄하는 클래스
     * 채널을 관리하고, 로그를 전역적으로 출력한다. 
     */
    class CLogManager 
    {
    private:
        typedef std::map<NLog::LogChannel, slogger> logs;

    private:
        static CLogManager maInstance;
        logs maLogs;
        lock maLock;
        NLog::LogChannel maDefaultChannel;

    public:
        static CLogManager * GetInstance();

        static void Finalize();

        void RemoveLogger( const NLog::LogChannel & irChannel );
        bool AddLogger( const NLog::LogChannel & irChannel, NLog::LogType iaType );

        bool SetDefaultChannel( const NLog::LogChannel & irChannel );

        bool IsExist( const NLog::LogChannel & irChannel );

        void Log( const NLog::LogChannel & irChannel, const string & irString );
        void LogDefault( const string & irString );
        void LogWithLevel( const NLog::LogChannel & irChannel, NLog::LevelType iaLevel, const string & irString );
        void LogWithLevelForDefaultChannel( NLog::LevelType iaLevel, const string & irString );
        void LogWithAllArg( const NLog::LogChannel & irChannel, string & irSrcFile, const uint32 iaLine, 
            const NLog::LevelType iaLevel, const string & irLogString );

    private:
        CLogManager();
        ~CLogManager();

        void RemoveAllLogger();
    };
}