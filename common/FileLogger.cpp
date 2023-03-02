#include "FileLogger.h"

CFileLogger::CFileLogger( const string & irFileName ) : maFileOut()
{
    Initialize( irFileName );
}
CFileLogger::~CFileLogger()
{

}

void CFileLogger::LogOut( const string & irString )
{
    maFileOut << irString;
}

void CFileLogger::Initialize( const string & irFileName )
{
    maFileOut.Open( irFileName, NFile::NMode::DWRITE);
}
