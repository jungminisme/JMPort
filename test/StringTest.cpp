#include "../common/JMString.h"
#include <iostream>

int main()
{
    JMLib::string aString;
    aString << L"Hello world";
    std::wcout << aString.c_str() << std::endl;
    return 0;
}