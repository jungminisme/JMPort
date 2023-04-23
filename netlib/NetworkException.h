#pragma once
#include "IException.h"

namespace JMLib
{
    namespace NetLib 
    {
        typedef uint16 ret_code;
        namespace NCode 
        {
            ret_code DNOT_INIT  = 1;
        }

        class CNetworkException : public IException 
        {
            private:
            NError::Level maLevel;
            ret_code maCode;
            string maMessage;
            
            public:
            CNetworkException() = default;
            ~CNetworkException() = default;

            CNetworkException( NError::Level iaLevel, ret_code iaCode, const string & irString  );
            NError::Level GetErrorLevel() const;
            const string & GetErrorMessage() const;
            ret_code GetErrorCode() const;
        };
    }
}