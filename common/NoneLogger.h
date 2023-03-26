#pragma once
#include "Logger.h"

namespace JMLib 
{
    /**
     * @brief NoneLogger 는 아무것도 하지 않는 Logger이다. 
     * 로그를 받아서 무시하는 역할 
     * 적어 놓은 로그를 모두 찾아서 지우기 싫을 때 해당 채널에 NoneLogger를 할당한다. 
     */
    class CNoneLogger : public CLogger
    {
        public:
        CNoneLogger( NLog::LevelType iaLevel = NLog::NLevel::DNONE) : CLogger( NLog::NLevel::DNONE) {}
        ~CNoneLogger() {}

        void Log( const string & irString )
        {}

        void SetLevel( const NLog::LevelType iaLevel ) 
        { 
            CLogger::SetLevel( NLog::NLevel::DNONE ); 
        }
        
        void LogWithLevel( const NLog::LevelType iaType, const string & irString )
        {}
        void LogWithAllArg( const string & irSrcFile, const uint32 iaLine, 
            const NLog::LevelType iaLevel, const string & irLogString )
        {}

        private:
        void LogOut( const string & irString )
        {
            return;
        }
    };

}