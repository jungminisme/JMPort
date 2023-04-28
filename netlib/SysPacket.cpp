#include "SysPacket.h"
#include "NetworkException.h"

using namespace JMLib::NetLib;

CSysPacket::CSysPacket(int32 iaOwner, cmd iaCmd ) 
    : maCommand( iaCmd ), maOwner( iaOwner )
{
}

CSysPacket::~CSysPacket() 
{

}

void CSysPacket::SetOwner( int32 iaOwner )
{
    maOwner = iaOwner;
}

JMLib::int32 CSysPacket::Owner() const
{
    return maOwner;
}

JMLib::cmd CSysPacket::Command() const
{
    return maCommand;
}

JMLib::uint32 CSysPacket::Size() const
{
    return DHEADER_SIZE;
}

char * CSysPacket::GetBuffer()
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return NULL;
}

JMLib::IPacket & CSysPacket::operator << ( const string & irVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const uint8 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const uint16 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const uint32 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const int8 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const int16 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const int32 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const bool iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const float32 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator << ( const float64 iaVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( string & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( uint8 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( uint16 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( uint32 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( int8 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( int16 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( int32 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( bool & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( float32 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}

JMLib::IPacket & CSysPacket::operator >> ( float64 & orVal ) 
{
    throw CNetworkException( NError::NLevel::DWARN, L"Invalid call , this is syspacket!");
    return * this;
}