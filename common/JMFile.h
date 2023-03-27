#pragma once
#include "JMString.h"
#include <fstream>

namespace JMLib 
{
    namespace NFile
    {
        typedef uint8 mode;
        typedef uint8 status;

        // file open의 Mode , binary mode open은 필요해질때 만든다. 
        namespace NMode 
        {
            const static mode DREAD = 1;
            const static mode DWRITE = 2;
            const static mode DREAD_WRITE = 3;
        }

        // CFile 의 상태, 닫힘. 읽기모드 오픈, 쓰기모드 오픈, 읽기쓰기 오픈
        namespace NStatus
        {
            const static status DCLOSE = 0;
            const static status DOPEN_READ = 1;
            const static status DOPEN_WRITE = 2;
            const static status DOPEN_RW = 3;   
        }
    }

    /**
     * @brief stream 을 Wrapping 한다. 
     * 주 목적은 maStream 을 guard하는 것. 객체 소멸시 close 한다. 
     * 다른 목적은 string을 이용한 File open, Write등 의 서비스 함수
     * 파일을 바이너리 모드로 읽고 쓰는 건 하지 않는다. 데이터는 DB혹은 XML로 저장한다. 
     * 게임 서버쪽에서  바이너리 모드 파일은 쓸일이 별로 없다.  
     */
    class CFile
    {
    private:
        std::wfstream maStream;
        NFile::status maStatus;    
    
    public:
        CFile() ;
        CFile( const string & irFileName, NFile::mode iaMode  );
        CFile( const wchar_t * ipFileName, NFile::mode iaMode );
        ~CFile();
        bool Open( const string & irFileName, NFile::mode iaMode );
        bool Open( const wchar_t * ipFileName, NFile::mode iaMode );

        int32 Append( const string & irString );
        int32 Append( const wchar_t * ipString );
        int32 AppendLine( const string & irString );
        int32 AppendLine( const wchar_t * ipString );
        int32 AppendNewLine( );
        int32 ReadLine( string & orString );
        CFile & operator << ( const string & irString );
        CFile & operator << ( const wchar_t * ipString );
        CFile & operator >> ( string & orString );

        bool IsOpen() const;

        int32 Size();
        void Close();
    };

}