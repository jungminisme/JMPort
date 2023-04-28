#pragma once
#include "JMString.h"

namespace JMLib 
{
    typedef uint16 cmd;
    
    namespace NetLib 
    {
        typedef int32 fd;
        typedef uint16 port;

        const static uint16 DMAX_PACKET_SIZE    = 4096;     //! 패킷의 최대 길이
        const static uint16 DHEADER_SIZE        = 6;        //! 해더의 크기 
        const static uint16 DPACKET_IDENTIFIER  = 38571;    //! 내 패킷인지 확인하는데 씀
    }

    namespace Packet
    {
        namespace Sys           //! 통신이 아닌 시스템에서 사용해야 할 command 종류
        {
            const static cmd DSYS_START         = 65000;
            const static cmd DCONNECT           = DSYS_START + 1;
            const static cmd DCLOSE             = DSYS_START + 2;
            const static cmd DERROR             = DSYS_START + 3;
        }
    }
}