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
        typedef std::basic_string<wchar_t> bsstring;

        string() {}
        string( bsstring & irString ) : maString( irString ) {}
        string( const wchar_t * ipString ) : maString( ipString ) {}
        string( string & irString ) : maString( irString.maString) {}

        /// @brief 문자열 비교 함수 
        /// @param irString , 비교를 원하는 문자열
        /// @return  입력된 문자열보다 현재 문자열이 순서상 앞인경우 음수, 같으면 0, 순서상 뒤는 양수
        int32 Compare( const string & irString )
        {
            return maString.compare( irString.maString );
        }

        /// @brief 빈문자열인지 확인
        /// @return 비어있으면 true, 내용이 있으면 false
        bool IsEmpty() const 
        {
            return maString.empty();
        }

        /// @brief 현재 문자열의 길이를 구한다. 
        /// @return 문자열의 길이
        uint32 Size() const 
        {
            return (uint32) maString.size();
        }

        /// @brief 문자열의 현재 내용 뒤로 입력 문자열을 추가 
        /// @param irString  추가를 원하는 문자열
        void Append( const string & irString )
        {
            maString.append( irString.maString.c_str() );
        }

        /// @brief 문자열의 현재 내용 뒤로 일반 문자열 추가 
        /// @param ipString 추가를 원하는 문자열
        void Append( const wchar_t * ipString )
        {
            maString.append( ipString );
        }

        /// @brief 문자열의 내용을 입력 문자열의 내용으로 변경
        /// @param irString 입력 문자열
        void Assign( const string & irString )
        {
            maString.assign( irString.maString );
        }

        /// @brief 문자열의 내용을 입력 문자열의 내용으로 변경
        /// @param ipString 입력 문자열
        void Assign( const wchar_t * ipString )
        {
            maString.assign( ipString );
        }

        /// @brief 현재 문자열의 내용을 지운다. 
        void Clear() 
        {
            maString.clear();
        }

        /// @brief ioStream 비슷한 형태의 구문으로 문자엘에 다른 문자열 추가하는 함수 
        /// @param irString 추가를 원하는 문자열
        /// @return 자신을 반환 . << 가 연속되는 경우를 지원한다. 
        string & operator << (const string & irString ) 
        {
            maString.append( irString.maString.c_str() );
            return * this;
        }

        /// @brief ioStream 비슷한 형태의 구문으로 문자열에 일반 스트링을 추가 
        /// @param ipString 일반 문자열 입력
        /// @return 자신을 반환 . << 가 연속되는 경우를 지원한다. 
        string & operator << ( const wchar_t * ipString )
        {
            maString.append( ipString );
            return * this;
        }

        const wchar_t * c_str() const
        {
            return maString.c_str();
        }

        /// @brief + 연산자를 이용한 문자열 추가 
        /// @param irString 추가를 원하는 문자열
        /// @return 자신을 반환 + 연속되는 경우를 지원한다. 
        string & operator + ( const string & irString )
        {
            maString.append( irString.maString.c_str() );
            return * this;
        }

        /**
         * @brief  + 연산자를 이용한 문자열 추가 
         * 
         * @param ipString 추가를 원하는 문자열
         * @return string&  연속된 + 나 다른 연산을 위해서 자신을 반환
         */
        string & operator + ( const wchar_t * ipString )
        {
            maString.append( ipString );
            return * this;
        }

        /**
         * @brief = 연산자를 이용한 할당
         * 
         * @param irString 원래의 문자열
         * @return string&  할당된 문자열, 여기의 경우 this
         */
        string & operator = ( const string & irString )
        {
            maString.assign( irString.maString.c_str() );
            return * this;
        }

        /**
         * @brief = 연산자를 이용한 할당
         * 
         * @param ipString 원래의 문자열
         * @return string& 할당된 문자열, 여기의 경우 this
         */
        string & operator = ( const wchar_t * ipString )
        {
            maString.assign( ipString );
            return * this;
        }

        /// @brief 좌우가 같은 문자열인지 비교
        /// @param irString 비교를 원하는 문자열
        /// @return 좌우 문자열이 같은 경우 true, 같지 않은 경우 false  
        bool operator == ( const string & irString ) const 
        {
            return maString == irString.maString;
        }

        /// @brief 문자열 좌우의 여백을 제거한다. 
        /// @param irDel 제거할 여백의 종류
        void Trim( const string & irDel = L"\t\n\v" )
        {
            maString.erase( maString.find_last_not_of(irDel.maString) + 1);
            maString.erase( maString.find_first_not_of(irDel.maString ));
        }

        /// @brief 좌우가 같지 않은 문자열인지 비교
        /// @param irString 비교를 원하는 문자열
        /// @return 좌우 문자열이 같은 경우 false, 같지 않은 경우 true
        bool operator != ( const string & irString ) const 
        {
            return maString != irString.maString;
        }
    };

}