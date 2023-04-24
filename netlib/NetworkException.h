#pragma once
#include "IException.h"

namespace JMLib
{
    namespace NetLib 
    {
        /**
         * @brief Netlib을 위한 exception
         * 거의 모든 exception이 비슷해 질것 같기는 하지만 우선 만들어 둔다. 
         * std::exception을 상속 받아 관련한 기능들이 모두 동작한다. 
         */
        class CNetworkException : public IException 
        {
            private:
            NError::Level maLevel;
            string maMessage;

            public:
            ~CNetworkException() = default;
            CNetworkException( NError::Level iaLevel, const string & irString );

            NError::Level GetErrorLevel() const;
            const string & GetErrorMessage() const;

            const char * what() const noexcept override;
        };
    }
}