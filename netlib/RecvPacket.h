#pragma once
#include "Packet.h"
namespace JMLib::NetLib
{
    class CRecvPacket : public CPacket
    {

        public:
        CRecvPacket( int32 iaOwner );
        ~CRecvPacket();

        void SetRead( uint16 iaSize );
    };
} 
