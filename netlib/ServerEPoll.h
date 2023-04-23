#pragma once
#include "ICallback.h"

namespace JMLib::NetLib
{
    class CServerEPoll : public IServer 
    {
        public:
        CServerEPoll() = default;
        ~CServerEPoll() = default;

        bool Init( const uint8 ipPort, const ICallback & irCallback );
        int32 Send( const IPacket & irPacket ) const;
    };
}