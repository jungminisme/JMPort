#include "RecvPacket.h"
#include "NetworkException.h"

using namespace JMLib::NetLib;

CRecvPacket::CRecvPacket( int32 iaOwner) : CPacket( iaOwner )
{
}

CRecvPacket::~CRecvPacket() 
{

}

void CRecvPacket::SetRead( uint16 iaSize )
{
    if( iaSize < DHEADER_SIZE )
        throw CNetworkException( NError::NLevel::DERROR, L"Invalid data size ");
    maPos = 0;
    uint16 aIdentifier;
    ReadFromBuffer( &aIdentifier, sizeof( uint16 ) );
    if( aIdentifier != DPACKET_IDENTIFIER )
        throw CNetworkException( NError::NLevel::DERROR, L"It is not JMPort Packet!");
    ReadFromBuffer( &maCommand, sizeof(uint16));
    ReadFromBuffer( &maSize, sizeof( uint16 ));
}
