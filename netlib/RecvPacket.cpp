#include "RecvPacket.h"
#include "NetworkException.h"

using namespace JMLib::NetLib;

CRecvPacket::CRecvPacket( int32 iaOwner) : CPacket( iaOwner )
{
}

CRecvPacket::~CRecvPacket() 
{

}

char * CRecvPacket::GetBuffer() 
{
    return maBuffer;
}

/**
 * @brief 읽혀진 양을 설정한다. 
 * dataBuffer에 이미 Data가 복사 되었다고 가정하고 시작하는 함수 
 * 그냥 Data Size 만을 설정하는 것이 아니라. Header부분을 해석한다. 
 * 
 * @param iaSize 
 */
void CRecvPacket::SetRead( uint16 iaSize )
{
    if( iaSize < DHEADER_SIZE )     // HeaderSize보다 읽힌 양이 적으면 안된다. 
        throw CNetworkException( NError::NLevel::DERROR, L"Invalid data size ");
    maSize = iaSize;
    maPos = 0;
    uint16 aIdentifier;
    *this >> aIdentifier >> maCommand >> maSize;
    if( aIdentifier != DPACKET_IDENTIFIER ) // 패킷이 정해진 양식인지 간단히 판단한다. 
        throw CNetworkException( NError::NLevel::DERROR, L"It is not JMPort Packet!");
    if( maSize != iaSize ) 
        throw CNetworkException( NError::NLevel::DERROR, L"Read size mismatch! ");
}
