#pragma once
#include "JMDataType.h"
#include "ICallback.h"
#include "IPacket.h"
#include "IServer.h"

namespace JMLib
{
    namespace NetLib 
    {
        /**
         * @brief Network 전체의 interface를 담당한다. 
         * 한서버가 여러개의 접속 주소를 돌리지는 않으니 singleton으로 관리한다. 
         */
        class CNetworkManager
        {
            private:
                server mpServer;

            public:
            static CNetworkManager & GetInstance();

            bool Init( const port iaPort, ICallback & irCallback );

            int32 Send ( const IPacket & irPacket ) const;

            private:
            CNetworkManager();
            ~CNetworkManager() = default;
        };
    }
}