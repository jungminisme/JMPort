#pragma once
#include "JMString.h"

namespace JMLib
{
    namespace NError
    {
        typedef uint8 Level;
        namespace NLevel
        {
            const static Level DTRACE = 1;   
            const static Level DDEBUG = 2;
            const static Level DINFO = 3;
            const static Level DWARN = 4;   
            const static Level DERROR = 5;
            const static Level DFATAL = 6;
        }
    }

    class IException 
    {
        protected:
        IException() = default;
        ~IException() = default;

        public:
        virtual const string & GetErrorMessage() const = 0;
        virtual NError::Level GetErrorLevel() const = 0;
    }
}