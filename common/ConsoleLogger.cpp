#include "ConsoleLogger.h"
#include <iostream>
using namespace JMLib;

/**
 * @brief 로그를 출력한다. 
 * iostream을 사용하여 출력한다. 출력후 줄바꿈한다. 
 * @param irString 출력할 문자열
 */
void CConsoleLogger::LogOut( const string & irString )
{
    std::wcout.imbue(std::locale(""));
    std::wcout << irString.c_str() << std::endl;
}