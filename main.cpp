#include <iostream>
#include "JMString.h"

int main(int, char**) {
    JMLib::string aString( L"Hello World!!");
    std::wcout << aString.c_str() << std::endl;
}
