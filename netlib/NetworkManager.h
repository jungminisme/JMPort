#pragma once
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

            bool Init( const port iaPort, CActionLauncher & irLauncher );

            void Run( int32 iaWait = -1 );

            int32 Send ( IPacket & irPacket ) const;

            private:
            CNetworkManager();
            ~CNetworkManager() = default;
        };
    }
}