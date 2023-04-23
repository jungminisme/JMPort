#pragma once
#include "IException.h"

namespace JMLib
{
    namespace NetLib 
    {
        class CNetworkException : public IException 
        {
            private:
            NError::Level maLevel;
            string maMessage;

            public:
            CNetworkException() = default;
            ~CNetworkException() = default;

            CNetworkException( NError::Level iaLevel, const string & irString );
            NError::Level GetErrorLevel() const;
            const string & GetErrorMessage() const;
        };
    }
}