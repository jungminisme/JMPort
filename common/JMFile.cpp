#include "JMFile.h"
#include <stdlib.h>

CFile::CFile() : maStatus( NFile::NStatus::DCLOSE )
{
    maStream.imbue( std::locale("ko_KR.UTF-8") );
}

/**
 * @brief Construct a new CFile::CFile object
 * wchar_t 로 파일오픈 생성할때 사용
 * @param ipFileName 오픈할 파일의 이름
 * @param iaMode read, write, rw 중 선택
 */
CFile::CFile( const wchar_t * ipFileName, NFile::mode iaMode )
{
    maStream.imbue( std::locale("ko_KR.UTF-8") );
    Open( ipFileName, iaMode );
}

/**
 * @brief Construct a new CFile::Cfile object
 * 생성될때 파일을 연다.  코드를 줄이고 싶을때를 위한 서비스
 * @param irFileName 열고 싶은 파일 이름
 * @param iaMode 열기 모드 
 */
CFile::CFile(const string &irFileName, NFile::mode iaMode)
{
    maStream.imbue( std::locale("ko_KR.UTF-8") );
    Open( irFileName, iaMode );
}

/** 
 * 파일 객체가 소멸할때는 무조건 파일 스트림을 닫는다. 
*/
CFile::~CFile()
{
    Close();
}

/**
 * @brief 텍스트 모드로 파일을 연다. 
 * string 객체를 생성해서 Open하는 것이 귀찮아 만든 함수 
 * string의 길이 문제로 인하여 내부에서는 Open( string &, mode )를 호출한다. 
 * @param ipFileName open할 파일의 이름
 * @param iaMode  read 모드 일지, write모드 일지 rw모드 일지 선택한다. 
 * @return true 파일이 열린경우
 * @return false 파일이 이미 열려있거나 다른 이유로 실패한경우 
 */
bool CFile::Open( const wchar_t * ipFileName, NFile::mode iaMode )
{
    string aString(ipFileName);
    return Open( aString, iaMode );
}

/**
 * @brief 텍스트모드로 파일을 연다. 
 * JMLib은 JMString만을 사용하지만 파일은 char* 만 입력을 받는다. 
 * 문자열 변환은 우선 여기서만 사용하고, 다른 예외사항 발생하면 그때 관련 문자열 함수를 만든다. 
 * 쓰기 모드로 파일을 열때는. 현재 내용의 뒤로 추가할수 있는 모드로  std::io_base::app //append mode
 * 읽기 모드로 열때는 제일 앞에서 부터 읽을수 있도록 한다. 
 * @param irFileName open할 파일 이름 . 
 * @param iaMode  read 모드 일지, write모드 일지 rw모드 일지 선택한다. 
 * @return true 파일이 열린경우
 * @return false 파일이 이미 열려있거나 다른 이유로 실패한경우 
 */
bool CFile::Open( const string & irFileName,  NFile::mode iaMode)
{
    // 이미 열려 있는지 확인한다. 
    if( IsOpen() == true )
    {
        //TODO : 이후 이곳에 Exception을 집어 넣는다. 
        return false;
    }
    uint aNameLength = irFileName.Size();
    // 파일 이름이 너무 길지 않은지 확인 한다. 
    if( ( aNameLength > JMLib::DMAX_STRING_SIZE ) || ( aNameLength < 1 ) )
        return false;
    // 파일 이름을 char* 로 변환한다. 
    char aBuffer[JMLib::DMAX_STRING_SIZE];
    memset( aBuffer, 0, JMLib::DMAX_STRING_SIZE );
    wcstombs(aBuffer, irFileName.c_str(), aNameLength );
    aBuffer[ aNameLength -1] = 0;
    switch(iaMode)
    {
        case NFile::NMode::DREAD:
            maStream.open( aBuffer,  std::ios_base::in );
            maStatus = NFile::NStatus::DOPEN_READ;
            break;
        case NFile::NMode::DWRITE:
            maStream.open( aBuffer, std::ios_base::app );
            maStream.seekg( std::ios_base::end );
            maStatus = NFile::NStatus::DOPEN_WRITE;
            break;
        case NFile::NMode::DREAD_WRITE:
            maStream.open( aBuffer, std::ios_base::in | std::ios_base::out );
            maStatus = NFile::NStatus::DOPEN_RW;
            break;
        default:
            return false;
    }
    return maStream.is_open();
}

/**
 * @brief 파일 스트림에 문자열을 저장한다. 
 * 스트링이 유니코드 이므로 저장되는 문자열도 유니코드
 * @param irString 파일에 저장할 문자열 
 * @return int32 저장된 문자열의 길이 
 */
int32 CFile::Append( const string & irString )
{
    //! write or rw mode로 열려 있지 않으면 쓰지 못한다. 
    if( maStatus != NFile::NStatus::DOPEN_WRITE && maStatus != NFile::NStatus::DOPEN_RW )
        return 0;
    int32 aBeforePos = maStream.tellg();
    maStream << irString.c_str() << std::endl;
    int32 aAfterPos = maStream.tellg();
    return (aAfterPos - aBeforePos);
}

/**
 * @brief 문장을 라인단위로 추가 한다. 
 * 입력 받은 문자열 끝에 개행을 넣는다. 
 * @param irString 추가할 문자열
 * @return int32 추가된 문자열을 길이 
 */
int32 CFile::AppendLine( const string & irString )
{
    uint32 aStringSize = irString.Size();
    if( aStringSize < 1 )
        return 0;
    int32 aRet = Append( irString );
    if( aRet < (int32) aStringSize )
        return 0;
    maStream << std::endl;
    return ( aRet + 1 );
}

/**
 * @brief 파일 내용에 줄바꿈을 한다. New Line
 * 
 * @return int32 추가된 문자열의 길이
 */
int32 CFile::AppendNewLine()
{
    //! write or rw mode로 열려 있지 않으면 쓰지 못한다. 
    if( ( maStatus != NFile::NStatus::DOPEN_WRITE ) && ( maStatus != NFile::NStatus::DOPEN_RW ) )
        return 0;
    maStream << std::endl;
    return 1;
}

/**
 * @brief 파일로 부터 문자열을 읽는다. 
 * 라인단위로 순차적으로 읽어 문자열에 저장한다.
 * 다음 읽을때는 현재 읽은 곳의 뒷부분이므로 반복하여 사용한다. 
 * @param orString 문자열을 반환할 스트링
 * @return int32 읽은 문자열의 길이
 */
int32 CFile::ReadLine( string & orString )
{
    //! read or rw mode 로 열려있지 않으면 읽지 못한다. 
    if( ( maStatus != NFile::NStatus::DOPEN_READ ) && ( maStatus != NFile::NStatus::DOPEN_RW ) )
        return 0;   
    wchar_t aBuffer[DMAX_STRING_SIZE];
    maStream.getline( aBuffer, DMAX_STRING_SIZE);
    orString.Assign(aBuffer );
    return orString.Size();
}

/**
 * @brief 파일이 현재 열려진 상태인지 알려준다. 
 * 
 * @return true 파일이 현재 열력있음 read or write 할수 있음.
 * @return false 파일이 열려 있지 않음. read and write 불가
 */
bool CFile::IsOpen() const 
{
    if( maStatus == NFile::NStatus::DCLOSE )
        return false;
    return true;
}

/**
 * @brief 파일로부터 문자열을 읽는다. 
 *  File >> string >> string; 의 형태를 지원한다.
 * @param orString 출력 스트링
 * @return CFile& 현재 파일 
 */
CFile & CFile::operator >> ( string & orString )
{
    ReadLine( orString );
    return * this;
}

/**
 * @brief 파일에 문자열을 저장한다. 
 * File << string << string; 의 형태를 지원한다. 
 * @param irString  저장할 문자열
 * @return CFile& 현재 파일
 */
CFile & CFile::operator << ( const string & irString )
{
    Append( irString );
    return * this;
}
/**
 * @brief 파일을 닫는다. 
 * 
 */
void CFile::Close()
{
    if( maStream.is_open() == true )
        maStream.close();
    maStatus = NFile::NStatus::DCLOSE;
}

/**
 * @brief 스트림의 전체 크기를 구한다. 
 * 현재위치를 왔다갔다 해야 하니 주의 한다. 
 * @return int32 파일의 크기 음수인경우 사이즈 읽기에 실패한 것이다. 
 */
int32 CFile::Size() 
{
    if( maStatus == NFile::NStatus::DCLOSE )
        return 0;
    /// 현재 위치를 기억해 놓는다. 
    int32 aCur = maStream.tellg();
    if( aCur < 0 )
        return aCur;
    /// 위치를 끝으로 보낸다. 
    maStream.seekg( 0, std::ios::end );
    /// 시작점으로 부터끝까지의 상대거리를 찾는다. 
    int32 aSize = maStream.tellg();
    /// 위치를 다시 현재위치로 옮긴다. 
    maStream.seekg( aCur );
    return aSize;
}
