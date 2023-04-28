#pragma once
#include "Packet.h"

namespace JMLib::NetLib
{
    /**
     * @brief Server에서 Client에게 메시지를 보낼때 패킷 (outbound)
     * 
     */
    class CSendPacket : public CPacket
    {
        public:
        CSendPacket( int32 iaOwner = 0, cmd iaCmd = 0 );
        ~CSendPacket();

        char * GetBuffer();
        private:
        void SetHeader();
    };
}