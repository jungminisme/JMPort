#include "Packet.h"
#include <string.h>
#include "NetworkException.h"

using namespace JMLib::NetLib;

CPacket::CPacket(int32 iaOwner ) : maOwner(0), maPos(0), maSize(0), maCommand(0)
{
        bzero( maBuffer, DMAX_PACKET_SIZE );
}

CPacket::~CPacket() 
{

}

void CPacket::SetOwner(int32 iaOwner)
{
    maOwner = iaOwner;
}

JMLib::int32 CPacket::Owner() const
{
    return maOwner;
}

JMLib::uint16 CPacket::Command() const 
{
    return maCommand;
}

JMLib::uint32 CPacket::Size() const
{
    return (uint32) maSize;
}

char * CPacket::GetBuffer() 
{
    return maBuffer;
}

JMLib::IPacket & CPacket::operator << ( const string & irVal ) 
{
    uint16 aDataLength = irVal.Size() * sizeof( wchar_t );
    AddToBuffer( (void * )irVal.c_str(), aDataLength );
    maBuffer[maSize++] = 0;        //! string null terminate해서 주고 받는다. 
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const uint8 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const uint16 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const uint32 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const int8 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const int16 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const int32 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const bool iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const float32 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator << ( const float64 iaVal )
{
    AddToBuffer( (void * ) &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( string & irVal )
{
    char * pStart = maBuffer + maPos;
    irVal.Assign( (wchar_t * ) pStart );
    uint8 aSize = irVal.Size() * sizeof( wchar_t) + 1;
    maPos += aSize;
    if( maPos > maSize )
        throw CNetworkException( NError::NLevel::DERROR, L"PacketSize underflow ");
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( uint8 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( uint16 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( uint32 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( int8 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( int16 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( int32 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( bool iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( float32 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( float64 iaVal )
{
    ReadFromBuffer( &iaVal, sizeof( iaVal ) );
    return * this;
}

void CPacket::AddToBuffer( void * pData, uint16 iaLength ) 
{
    if( ( iaLength + maSize ) > DMAX_PACKET_SIZE ) {
        throw CNetworkException( NError::NLevel::DERROR, L"PacketSize overflow ");
    }
    char * pStart = maBuffer + maSize;
    memcpy( pStart, pData, (size_t) iaLength );
    maSize += iaLength;
}

void CPacket::ReadFromBuffer( void * pData, uint16 iaLength )
{
    if( (iaLength + maPos ) > maSize ) 
        throw CNetworkException( NError::NLevel::DERROR, L"PacketSize underflow " );
    char * pRead = maBuffer + maPos;
    memcpy( pData, pRead, (size_t) iaLength );
    maPos += iaLength;
}