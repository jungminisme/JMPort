#include "Packet.h"
#include <string.h>
#include "NetworkException.h"

using namespace JMLib::NetLib;

CPacket::CPacket(int32 iaOwner ) : maOwner(iaOwner), maPos(0), maSize(0), maCommand(0)
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

JMLib::cmd CPacket::Command() const 
{
    return maCommand;
}

JMLib::uint32 CPacket::Size() const
{
    return (uint32) maSize;
}

/**
 * @brief Packet에 문자열을 추가한다. 
 * 문자열의 길이는 따로 계산을 해서, null 을 포함한 길이 만큼 버퍼에 추가한다. 
 * gcc는 wchar_t가 4byte 윈도우 2byte 이다. 
 * UTF-8 로 변환하여 데이터를 보내고 받자. 
 * @param irVal 추가할 문자열
 * @return JMLib::IPacket&  *this 를 반환한다. Packet << data1 << data2 ; 이런 형태 지원
 */
JMLib::IPacket & CPacket::operator << ( const string & irVal ) 
{
    std::string aSend = irVal.WstrToUTF8();
    uint16 aDataLength = aSend.size();
    AddToBuffer( (void * )aSend.c_str(), aDataLength );
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

/**
 * @brief 패킷으로 부터 문자열을 읽어온다. 
 * 문자열이 언제 끝날지 알수 없으니까. 문자열 읽기는 std::string을 믿는다. 
 * 읽어놓고 나서 읽혀진 문자열의 길이 만큼 현재의 pos를 뒤로 밀어준다. 
 * gcc와 Visual C 의 wchar_t 사이즈 차이를 고려하여 UTF-8 로 보내고 받는다. 
 * @param orVal 반환받을 문자열의 reference. Output param 
 * @return JMLib::IPacket&  * this , Packet >> data1 >> data2; 의 형태를 지원
 */
JMLib::IPacket & CPacket::operator >> ( string & orVal )
{
    char * pStart = maBuffer + maPos;
    std::string aStrOut = pStart;
    orVal.UTF8ToWstr( aStrOut );
    uint8 aSize = aStrOut.size() + 1;
    maPos += aSize;
    if( maPos > maSize )
        throw CNetworkException( NError::NLevel::DERROR, L"PacketSize underflow ");
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( uint8 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( uint8 ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( uint16 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( uint16 ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( uint32 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( uint32 ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( int8 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( int8 ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( int16 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( int16 ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( int32 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( int32 ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( bool & orVal )
{
    ReadFromBuffer( &orVal, sizeof( bool ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( float32 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( float32 ) );
    return * this;
}

JMLib::IPacket & CPacket::operator >> ( float64 & orVal )
{
    ReadFromBuffer( &orVal, sizeof( float64 ) );
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