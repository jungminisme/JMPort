#include "FileLogger.h"

using namespace JMLib;

CFileLogger::CFileLogger() : maFileOut()
{
}

CFileLogger::~CFileLogger()
{

}

/**
 * @brief 파일에 문자열을 적는다. 
 * \n은 File 클래스에서 집어넣는다. 
 * @param irString 출력될 로그
 */
void CFileLogger::LogOut( const string & irString )
{
    maFileOut.AppendLine( irString );
}

/**
 * @brief 로거를 초기화 한다. 
 * 입력된 파일내임으로 파일을 열어 적을 준비를 한다. 
 * @param irFileName 열릴 파일 이름
 */
void CFileLogger::Initialize( const string & irFileName )
{
    maFileOut.Open( irFileName, NFile::NMode::DWRITE );
}
