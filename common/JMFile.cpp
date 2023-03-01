#include "JMFile.h"


CFile::CFile() 
{
}

CFile::~CFile()
{
    if( maStream.is_open() == true )
        maStream.close();
}

bool CFile::Open( const string & irFileName,  NFile::mode iaMode)
{
    std::wstring aString;
    aString.assign( irFileName.c_str() );
    if(maStream.is_open() == true )
    {
        //:TODO 이후 이곳에 Exception을 집어 넣는다. 
        return false;
    }
 //   std::io_base::openmode
 /*
 //:TODO unicode filename을 이용한 fstream open 이 존재하지 않음.  
    switch(iaMode)
    {
        case NFile::NMode::DREAD:
            maStream.open( aString,  std::ios_base::in );
        break;
        case NFile::NMode::DWRITE:
            maStream.open( aString, )
    }
    */
}