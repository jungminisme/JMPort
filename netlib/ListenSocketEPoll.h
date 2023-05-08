#pragma once
#include "SocketEPoll.h"
#include "ServerEPoll.h"

namespace JMLib::NetLib
{
    /**
     * @brief Client의 연결 요청만을 처리하는 소켓 
     * accept를 대기하고만 있기에 listenSocket이라고 이름 붙인다. 
     */
    class CListenSocketEPoll : public CSocketEPoll
    {
        private:
        const static int32 DMAX_BACKLOG = 10; //! 최대 Listen backlog 갯수

        protected:
        CServerEPoll & mrServer;

        public:
        CListenSocketEPoll( CServerEPoll & irServer, CActionLauncher & irCallback );
        ~CListenSocketEPoll();

        void Init( const port iaPort );
        virtual int32 OnEvent();
        int32 Send( IPacket & irPacket ) const;

        private:
        void Create();
        void Bind( const port iaPort );
        void Listen();
        
        protected:
        void OnAccept( esock iaSock );
    };
}