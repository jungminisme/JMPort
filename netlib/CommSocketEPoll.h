#pragma once
#include "SocketEPoll.h"
#include "ServerEPoll.h"

namespace JMLib::NetLib
{
    /**
     * @brief Client와 통신을 할 Socket
     * ClientSocket은 클라이언트 구현할때 쓸것 같아서. 
     * 통신용 소켓이라는 의미(Listener의 반대)로 Communication Socket으로 명명한다. 
     */
    class CCommSocketEPoll : public CSocketEPoll
    {
        private:
        uint16 maPort;                  //! 접속된 포트
        uint32 maPublicAddr;            //! 공용 IP의 주소
        uint32 maPrivateAddr;           //! 사설 IP의 주소

        CServerEPoll & mrServer;        //! 자신을 관리하는 Server

        public:
        CCommSocketEPoll( CActionLauncher & irLauncher, CServerEPoll & irServer );
        ~CCommSocketEPoll();

        int32 OnEvent();
        int32 Send( IPacket & irPacket ) const;
        void Init( fd iaFD, port iaPort, uint32 iaAddr );
        void OnClose();

        private:
        void onRecvError() const;
    };
}