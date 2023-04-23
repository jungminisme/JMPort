#pragma once
#include "IServer.h"

namespace JMLib::NetLib
{
    /**
     * @brief Client의 연결 요청만을 처리하는 소켓 
     * 
     */
    class CListenSocketEPoll 
    {
        private:
        const static int32 DMAX_BACKLOG = 10; //! 최대 Listen backlog 갯수

        private:
        fd maListenFD;
        IServer &  mrServer;

        public:
        CListenSocketEPoll( const IServer & irServer );
        ~CListenSocketEPoll();

        void Init( const uint16 iaPort );
        const fd GetFD() const;
        void Close();

        private:
        void Create();
        void Bind();
        void Listen();
    };
}