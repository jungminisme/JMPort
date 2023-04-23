#pragma once
#include "JMDataType.h"
#include "ICallback.h"
#include "IPacket.h"

namespace JMLib
{
    namespace NetLib 
    {

        class IServer 
        {
            public:
            virtual bool Init( const uint8 iaPort, const ICallback & irCallback ) = 0;
            virtual int32 Send( const IPacket & irPacket ) const = 0;

            protected:
            IServer() = default;
            ~IServer() = default;
        };
        typedef std::shared_ptr< IServer > server;

        class CNetworkManager
        {
            private:
                server mpServer;
            public:
            static CNetworkManager & GetInstance();

            bool Init( const uint8 iaPort, const ICallback & irCallback );

            int32 Send ( const IPacket & irPacket ) const;

            private:
            CNetworkManager() = default;
            ~CNetworkManager() = default;
        };
    }
}