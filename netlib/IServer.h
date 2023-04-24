#pragma once
#include "JMDataType.h"
#include "ICallback.h"
#include "IPacket.h"
namespace JMLib
{

    namespace NetLib 
    {
        typedef int32 fd;
        typedef uint16 port;
        
        /**
         * @brief Server Interface 
         * Interface로 뭔가를 한다기 보다는. 외부에서 NetworkManager를 접근할때 
         * class 가시범위를 여기까지로 막기 위해 사용한다. 
         */
        class IServer 
        {
            public:
            virtual bool Init( const port iaPort, ICallback & irCallback ) = 0;
            virtual int32 Send( const IPacket & irPacket ) const = 0;

            protected:
            IServer() = default;
            ~IServer() = default;
        };

        typedef std::shared_ptr< IServer > server;
    }
}