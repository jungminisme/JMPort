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
        const static uint16 DPACKET_IDENTIFIER  = 4531;    //! 내 패킷인지 확인하는데 씀
        const static uint16 DMAX_READ_RETRY     = 10;       //! Packet이 끊어져서 왔을때 최대 다시읽는 횟수
        const static uint32 DREAD_INTERVAL      = 10;       //! Packet다시 읽기 할때 읽기간 쉬는 시간 
        const static uint16 DMAX_WRITE_RETRY    = 10;       //! Packet Write중 다 안써졌을때 다시 시도 횟수
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