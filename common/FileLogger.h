#pragma once
#include "Logger.h"
#include "JMFile.h"

using namespace JMLib;

class CFileLogger
{
    private:
    CFile maFileOut;
    public:
    CFileLogger( const string & irFileName );
    ~CFileLogger();

    void LogOut( const string & irString );

    void Initialize( const string & irFileName );
};