#pragma once
#include "ICallback.h"
#include "IServer.h"
#include "ListenSocketEPoll.h"

namespace JMLib::NetLib
{
    /**
     * @brief Epoll 방식으로 동작하는 서버 
     * 
     */
    class CServerEPoll : public IServer 
    {
        private:
        CListenSocketEPoll maListener;

        public:
        CServerEPoll();
        ~CServerEPoll();

        bool Init( const uint16 iaPort, const ICallback & irCallback );
        int32 Send( const IPacket & irPacket ) const;
    };
}