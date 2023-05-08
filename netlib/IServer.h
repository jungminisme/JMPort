#pragma once
#include "NetCommon.h"
#include "IPacket.h"
#include "ActionLauncher.h"
namespace JMLib
{
    namespace NetLib 
    {
        
        /**
         * @brief Server Interface 
         * Interface로 뭔가를 한다기 보다는. 외부에서 NetworkManager를 접근할때 
         * class 가시범위를 여기까지로 막기 위해 사용한다. 
         */
        class IServer 
        {
            public:
            virtual bool Init( const port iaPort, CActionLauncher & irLauncher ) = 0;
            virtual int32 Send( IPacket & irPacket ) const = 0;

            protected:
            IServer() = default;
            ~IServer() = default;
        };

        typedef std::shared_ptr< IServer > server;
    }
}