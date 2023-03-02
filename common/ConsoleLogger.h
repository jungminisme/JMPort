#pragma once
#include "Logger.h"
using namespace JMLib;

/**
 * @brief 로그를 화면에 출력하는 로거
 * 
 */
class CConsoleLogger : public CLogger
{
    public:
    CConsoleLogger() {}
    ~CConsoleLogger() {}

    void LogOut( const string & irString );
};