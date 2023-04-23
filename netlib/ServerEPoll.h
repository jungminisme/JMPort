#pragma once
#include "ICallback.h"
#include "IServer.h"

namespace JMLib::NetLib
{
    typedef int32 fd;
    /**
     * @brief Epoll 방식으로 동작하는 서버 
     * 
     */
    class CServerEPoll : public IServer 
    {
        private:
        const static int32 DMAX_BACKLOG = 10; //! 최대 Listen backlog 갯수

        private:
        fd maListenFD;

        public:
        CServerEPoll() = default;
        ~CServerEPoll() = default;

        bool Init( const uint16 iaPort, const ICallback & irCallback );
        int32 Send( const IPacket & irPacket ) const;
    };
}