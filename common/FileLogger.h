#pragma once
#include "Logger.h"
#include "JMFile.h"

using namespace JMLib;

class CFileLogger : public CLogger 
{
    private:
    CFile maFileOut;
    public:
    CFileLogger();
    ~CFileLogger();

    void LogOut( const string & irString );

    void Initialize( const string & irFileName );
};