#pragma once
#include "ICallback.h"
#include "IServer.h"
#include "SocketEPoll.h"

namespace JMLib::NetLib
{
    /**
     * @brief Epoll 방식으로 동작하는 서버 
     * 
     */
    class CServerEPoll : public IServer 
    {
        protected:
        const static int32 DMAX_EPOLL_EVENT     = 1024;
        const static int32 DEPOLL_TIME_OUT      = -1;

        protected:
        std::map< fd, esock > maSockets;
        fd maEPollFD;

        public:
        CServerEPoll();
        ~CServerEPoll();

        bool Init( const port iaPort, ICallback & irCallback );
        int32 Send( IPacket & irPacket ) const;
        void OnConnect( esock iaSock );

        int32 CheckSockets();

        private:
        void CreateEPoll( esock iaListener );
        void InsertSock( esock iaSock );
    };
}