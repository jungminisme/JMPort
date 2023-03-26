#pragma once
#include "Logger.h"

/**
 * @brief 로그를 화면에 출력하는 로거
 * 
 */
namespace JMLib 
{
    class CConsoleLogger : public CLogger
    {
        public:
        CConsoleLogger(NLog::LevelType iaLevel = NLog::NLevel::DALL) : CLogger( iaLevel ) {}
        ~CConsoleLogger() {}

        void LogOut( const string & irString );
    };

}