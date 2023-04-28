#pragma once
#include "IPacket.h"
namespace JMLib
{
    /**
     * @brief Callback을 위한 interface 
     * 선언은 이곳에 되어 있지만 실제 구현은 Contents 쪽에서 한다. 
     * 
     */
    class ICallback
    {
        protected:
        ICallback() = default;
        ~ICallback() = default;

        public:
        virtual int32 Post( const IPacket & irPacket ) const = 0;
    };
}