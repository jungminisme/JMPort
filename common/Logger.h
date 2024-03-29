#pragma once

#include "ILogger.h"
#include "Lock.h"

namespace JMLib 
{
    /**
     * @brief 각종 Logger들의 superclass
     *  LogOut을 제외한 모든 공통 작업들은 수행한다. 
     */
    class CLogger : public ILogger
    {
        private:
        /// @brief maLevel 이하의 Log는 출력하지 않는다. 
        uint8 maLevel;
        /// @brief Log를 ThreadSafe 하게 사용하기 위해 둔다. 
        lock maLock;

        public:
        CLogger( NLog::LevelType iaLevel = NLog::NLevel::DALL );
        virtual ~CLogger() = default;

        virtual void Initialize( const string & irString, const NLog::LevelType iaLevel = NLog::NLevel::DALL );
        virtual void SetLevel( const NLog::LevelType iaLevel );
        virtual void Log( const string & irString );
        virtual void LogWithLevel( const NLog::LevelType iaLevel, const string & irString );
        private:
        virtual void LogOut( const string & irString ) = 0;

    };

}