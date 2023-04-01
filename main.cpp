#include <iostream>
#include "JMString.h"

int main(int, char**) {
    JMLib::string aString( L"Hello .. world!!");
    std::wcout << aString.c_str() << std::endl;

    aString << L" and welcom to another world!!" ;

    std::wcout << aString.c_str() << std::endl;
}
