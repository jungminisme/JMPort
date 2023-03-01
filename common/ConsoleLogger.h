#pragma once

#include "Logger.h"

using namespace JMLib;

class CConsoleLogger : public CLogger
{
    public:
    CConsoleLogger() {}
    ~CConsoleLogger() {}

    void LogOut( const string & irString );
};