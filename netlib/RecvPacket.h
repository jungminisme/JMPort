#pragma once
#include "Packet.h"
namespace JMLib::NetLib
{
    /**
     * @brief Cient로부터 읽어들인 패킷 
     * Header부분을 해석 하는 역할을 주로 한다. 
     */
    class CRecvPacket : public CPacket
    {
        public:
        CRecvPacket( int32 iaOwner );
        ~CRecvPacket();

        void SetRead( uint16 iaSize );
    };
} 
