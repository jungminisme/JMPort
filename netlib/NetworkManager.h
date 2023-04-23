#pragma once
#include "JMDataType.h"
#include "ICallback.h"
#include "IPacket.h"
#include "IServer.h"

namespace JMLib
{
    namespace NetLib 
    {
        class CNetworkManager
        {
            private:
                server mpServer;

            public:
            static CNetworkManager & GetInstance();

            bool Init( const uint16 iaPort, const ICallback & irCallback );

            int32 Send ( const IPacket & irPacket ) const;

            private:
            CNetworkManager();
            ~CNetworkManager() = default;
        };
    }
}