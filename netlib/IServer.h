#pragma once
#include "JMDataType.h"
#include "ICallback.h"
#include "IPacket.h"
namespace JMLib
{

    namespace NetLib 
    {
        typedef int32 fd;
        
        class IServer 
        {
            public:
            virtual bool Init( const uint16 iaPort, const ICallback & irCallback ) = 0;
            virtual int32 Send( const IPacket & irPacket ) const = 0;

            protected:
            IServer() = default;
            ~IServer() = default;
        };
        typedef std::shared_ptr< IServer > server;
    }
}