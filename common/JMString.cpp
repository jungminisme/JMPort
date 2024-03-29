#include "JMString.h"
#include <codecvt>

using namespace JMLib;
string::string() 
{

}

string::string( const wchar_t * ipString ) : maString( ipString ) 
{

}

string::string( const string & irString ) : maString( irString.maString) 
{

}

string::string( const std::string & irString ) 
{
    StrToWstr( irString );
}

/// @brief 문자열 비교 함수 
/// @param irString , 비교를 원하는 문자열
/// @return  입력된 문자열보다 현재 문자열이 순서상 앞인경우 음수, 같으면 0, 순서상 뒤는 양수
int32 string::Compare( const string & irString )
{
    return maString.compare( irString.maString );
}

/// @brief 빈문자열인지 확인
/// @return 비어있으면 true, 내용이 있으면 false
bool string::IsEmpty() const 
{
    return maString.empty();
}

/// @brief 현재 문자열의 길이를 구한다. 
/// @return 문자열의 길이
uint32 string::Size() const 
{
    return (uint32) maString.size();
}

/// @brief 문자열의 현재 내용 뒤로 입력 문자열을 추가 
/// @param irString  추가를 원하는 문자열
void string::Append( const string & irString )
{
    maString.append( irString.maString.c_str() );
}

/// @brief 문자열의 현재 내용 뒤로 일반 문자열 추가 
/// @param ipString 추가를 원하는 문자열
void string::Append( const wchar_t * ipString )
{
    maString.append( ipString );
}

/// @brief 문자열의 내용을 입력 문자열의 내용으로 변경
/// @param irString 입력 문자열
void string::Assign( const string & irString )
{
    maString.assign( irString.maString );
}

/// @brief 문자열의 내용을 입력 문자열의 내용으로 변경
/// @param ipString 입력 문자열
void string::Assign( const wchar_t * ipString )
{
    maString.assign( ipString );
}

/// @brief 현재 문자열의 내용을 지운다. 
void string::Clear() 
{
    maString.clear();
}

/// @brief ioStream 비슷한 형태의 구문으로 문자엘에 다른 문자열 추가하는 함수 
/// @param irString 추가를 원하는 문자열
/// @return 자신을 반환 . << 가 연속되는 경우를 지원한다. 
string & string::operator << (const string & irString ) 
{
    maString.append( irString.maString.c_str() );
    return * this;
}

/// @brief ioStream 비슷한 형태의 구문으로 문자열에 일반 스트링을 추가 
/// @param ipString 일반 문자열 입력
/// @return 자신을 반환 . << 가 연속되는 경우를 지원한다. 
string & string::operator << ( const wchar_t * ipString )
{
    maString.append( ipString );
    return * this;
}

const wchar_t * string::c_str() const
{
    return maString.c_str();
}

/// @brief + 연산자를 이용한 문자열 추가 
/// @param irString 추가를 원하는 문자열
/// @return 자신을 반환 + 연속되는 경우를 지원한다. 
string & string::operator + ( const string & irString )
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
string & string::operator + ( const wchar_t * ipString )
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
string & string::operator = ( const string & irString )
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
string & string::operator = ( const wchar_t * ipString )
{
    maString.assign( ipString );
    return * this;
}

/// @brief 좌우가 같은 문자열인지 비교
/// @param irString 비교를 원하는 문자열
/// @return 좌우 문자열이 같은 경우 true, 같지 않은 경우 false  
bool string::operator == ( const string & irString ) const 
{
    return maString == irString.maString;
}

/**
 * @brief 비교 연산자
 * std::map 에 string이 key인 경우를 위해 제작한다
 * Dictionary order를 따른다. 
 * @param irString lhs value  *this < lsh
 * @return true  lsh 보다 *this 가 작은 경우
 * @return false lsh 보다 *this 가 작지 않은 경우, 같은 경우 포함
 */
bool JMLib::string::operator < (const string & irString) const
{
    return ( maString < irString.maString );
}

/// @brief 문자열 좌우의 여백을 제거한다. 
/// @param irDel 제거할 여백의 종류
void string::Trim( const string & irDel )
{
    maString.erase( maString.find_last_not_of(irDel.maString) + 1);
    maString.erase( 0, maString.find_first_not_of(irDel.maString ));
}

/// @brief 좌우가 같지 않은 문자열인지 비교
/// @param irString 비교를 원하는 문자열
/// @return 좌우 문자열이 같은 경우 false, 같지 않은 경우 true
bool string::operator != ( const string & irString ) const 
{
    return maString != irString.maString;
}

/**
 * @brief 문자열을 숫자로 변환
 * 
 * @return int32 변환된 숫자
 */
int32 string::ToInt() const
{
    if( std::regex_match(maString.c_str(), DINT_REG ) == true )
        return std::stoi( maString.c_str() );
    return 0;
}

/**
 * @brief 문자열을 float 로 변환
 * 
 * @return float64 변환된 숫자
 */
float64 string::ToFloat() const
{
    if( std::regex_match(maString.c_str(), DFLAOT_REG) == true )
        return std::stod( maString.c_str() );
    return 0;
}

/// @brief  포멧으로 문자열을 생성한다. 
/// @param ipFormat 문자열 생성포멧. printf에 쓰는 포멧들
/// @param  Format을 위한 파라미터들
/// @return 자신을 반환한다. 
string & string::Format( const wchar_t * ipFormat, ... )
{
    wchar_t aBuffer[DSTRING_BUFFER_SIZE];
    va_list aVarList;
    va_start( aVarList, ipFormat );
    vswprintf(aBuffer, DSTRING_BUFFER_SIZE, ipFormat, aVarList );
    va_end( aVarList );
    maString.assign(aBuffer);
    return * this;
}

/// @brief va_list를 받을 수 밖에 없는 경우의 포멧으로 문자열 생성
/// @param ipFormat 문자열 생성포멧
/// @param iaList 파라미터 리스트 
/// @return 자신을 반환
string & string::FormatWithVAList( const wchar_t * ipFormat, va_list iaList )
{
    wchar_t aBuffer[DSTRING_BUFFER_SIZE];
    vswprintf(aBuffer, DSTRING_BUFFER_SIZE, ipFormat, iaList);
    maString.assign(aBuffer);
    return * this;
}

/**
 * @brief char * 형태의 문자열을 쓸수 있도록 반환한다. 
 * File 과 Database때문에 만든다. 
 * @return std::string 현재 문자열을 복사한 MBCS 
 */
std::string string::WstrToStr() const
{
    return std::string().assign(maString.begin(), maString.end() );
}

/**
 * @brief std::string으로부터 문자열을 생성
 * File 과 Database때문에 만든다. 
 * @param irStr 입력 문자열
 */
void string::StrToWstr(const std::string &irStr)
{
    maString.assign( irStr.begin(), irStr.end() );
}

/**
 * @brief UTF8 문자열로 변환하여 반환한다. 
 * 이기종간의 문자열 전송을 위해 사용한다. 
 * @return std::string UTF8로 인코딩된 문자열
 */
std::string string::WstrToUTF8() const
{
    std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> aConv;
    return aConv.to_bytes( maString );
}

/**
 * @brief UTF8 문자열로부터 wchar_t 문자열을 생성한다. 
 * 이기종 간의 문자열 전송을 위해 사용한다. 
 * @param irStr UTF8 문자열
 */
void string::UTF8ToWstr( const std::string & irStr )
{
    std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> aConv;
    maString = aConv.from_bytes( irStr );
}