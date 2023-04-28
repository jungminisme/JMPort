#include "SendPacket.h"

using namespace JMLib::NetLib;
CSendPacket::CSendPacket(int32 iaOwner, cmd iaCmd) : CPacket( iaOwner)
{
    maSize = DHEADER_SIZE;
    maPos = DHEADER_SIZE;
    maCommand = iaCmd;
}

CSendPacket::~CSendPacket() 
{

}

char * CSendPacket::GetBuffer()
{
    SetHeader();
    return maBuffer;
}

/**
 * @brief 멤버 변수로 Header를 구성한다. 
 * GetBuffer에서만 부르고 할일도 별고 없지만. 의미상 함수를 나눈다. 
 */
void CSendPacket::SetHeader() 
{
    char * pWritePoint = maBuffer;
    memcpy( pWritePoint, &DPACKET_IDENTIFIER, sizeof( uint16 ));
    pWritePoint += sizeof( uint16 );
    memcpy( pWritePoint, &maCommand, sizeof( uint16 ) );
    pWritePoint += sizeof( uint16 );
    memcpy( pWritePoint, &maSize, sizeof( int16 ) );
}