#pragma once

#include <string>
#include <vector>
#include <stdarg.h>
#include <regex>

#include "JMDataType.h"

namespace JMLib
{
    const static uint32 DMAX_STRING_SIZE = 8012;
    const static std::wregex DINT_REG( L"^[-+]?[[:digit:]]+$");
    const static std::wregex DFLAOT_REG( L"^[+-]?[[:digit:]]*(.?[[:digit:]]*)$");

    /// @brief 문자열 클래스, wstring을 wrapping 한다. 
    class string
    {
        private:
        const static uint32 DSTRING_BUFFER_SIZE = DMAX_STRING_SIZE + 1;
        std::wstring maString;

        public:
        string();
        string( const wchar_t * ipString ) ;
        string( string & irString );
        int32 Compare( const string & irString );
        bool IsEmpty() const ;
        uint32 Size() const ;
        void Append( const string & irString );
        void Append( const wchar_t * ipString );
        void Assign( const string & irString );
        void Assign( const wchar_t * ipString );
        void Clear() ;
        string & operator << (const string & irString ) ;
        string & operator << ( const wchar_t * ipString );
        const wchar_t * c_str() const;
        string & operator + ( const string & irString );
        string & operator + ( const wchar_t * ipString );
        string & operator = ( const string & irString );
        string & operator = ( const wchar_t * ipString );
        bool operator == ( const string & irString ) const ;
        void Trim( const string & irDel = L"\t\n\v" );
        bool operator != ( const string & irString ) const ;
        int32 ToInt() const;
        float64 ToFloat() const;
        string & Format( const wchar_t * ipFormat, ... );
        string & FormatWithVAList( const wchar_t * ipFormat, va_list iaList );
    };

}