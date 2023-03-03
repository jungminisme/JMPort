#include "../common/JMDataType.h"
#include "../common/JMString.h"

#include <string>
#include <iostream>

using namespace JMLib;

int main()
{
    string aString = L"This is first sTring \n";
    std::wcout << aString.c_str() << std::endl;
  
    aString << L"More Line " ;

    std::wcout << aString.c_str() << std::endl;
    return 0;
}