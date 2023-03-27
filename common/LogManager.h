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
        logs maLogs;
        lock maLock;
        NLog::LogChannel maDefaultChannel;

    public:
        static CLogManager & GetInstance();

        static void Finalize();

        bool RemoveLogger( const NLog::LogChannel & irChannel );
        bool AddLogger( const NLog::LogChannel & irChannel, const NLog::LogType iaType, 
            NLog::LevelType iaLevel = NLog::NLevel::DALL );
        bool SetLevel( const NLog::LogChannel & irChannel, const NLog::LevelType iaLevel );

        void SetDefaultChannel( const NLog::LogChannel & irChannel );

        bool IsExist( const NLog::LogChannel & irChannel );

        void Log( const NLog::LogChannel & irChannel, const string & irString );
        void LogDefault( const string & irString );
        void LogWithLevel( const NLog::LogChannel & irChannel, NLog::LevelType iaLevel, const string & irString );
        void LogWithLevelForDefaultChannel( NLog::LevelType iaLevel, const string & irString );

    private:
        CLogManager();
        ~CLogManager();

        void RemoveAllLogger();
    };

}