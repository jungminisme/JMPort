#pragma once
#include "IServer.h"

namespace JMLib::NetLib
{
    /**
     * @brief EPoll을 위한 Socket 객체 최상위 클래스 
     * File Descriptor 와 관련한 기본동작을 한다. 
     * fd의 이벤트가 발생했을때의 처리를 위한 공통 함수의 인터페이스를 제공한다. OnEvent, Send
     */
    class CSocketEPoll
    {
        protected:
        fd maFD;
        ICallback & mrCallback;

        public:
        virtual int32 OnEvent() = 0;
        virtual int32 Send( IPacket & irPacket ) const = 0;
        const fd GetFD() const;
        void Close();
        
        protected:
        CSocketEPoll( ICallback & irCallback );
        virtual ~CSocketEPoll();
    };

    typedef std::shared_ptr<CSocketEPoll> esock;
}