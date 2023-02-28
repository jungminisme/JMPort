#pragma once

#include "ILogger.h"
#include "Lock.h"

using namespace JMLib;

/**
 * @brief 
 * 
 */
class CLogger : public ILogger{
    private:
    /// @brief maLevel 이하의 Log는 출력하지 않는다. 
    uint8 maLevel;
    /// @brief Log를 ThreadSafe 하게 사용하기 위해 둔다. 
    lock maLock;

    public:
    CLogger() {}
    ~CLogger() {}

    void Log( const string & irString );
    void LogWithLevel( const NLog::LevelType iaType, const string & irString );
    void LogWithAllArg( const string & irSrcFile, const uint32 iaLine, 
        const string & irChannel, const NLog::LevelType iaLevel, const string & irLogString );

};