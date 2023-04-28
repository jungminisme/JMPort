#include <gtest/gtest.h>
#include "SysPacket.h"
#include "SendPacket.h"

TEST( NetlibTest, PacketTest )
{
    JMLib::NetLib::CSendPacket aPacket;
    EXPECT_EQ( aPacket.Owner(), 0 );
    EXPECT_EQ( aPacket.Command(), 0 );
    EXPECT_EQ( aPacket.Size(), JMLib::NetLib::DHEADER_SIZE );
    aPacket.SetOwner( 32 );
    EXPECT_EQ( aPacket.Owner(), 32 );
    JMLib::string aStr = L"여기에 한글을 적는다";
    JMLib::uint8 aUint8  = 1; 
    JMLib::uint16 aUint16  = 2; 
    JMLib::uint32 aUint32  = 3; 
    JMLib::int8 aInt8  = 4; 
    JMLib::int16 aInt16  = 5; 
    JMLib::int32 aInt32  = 6; 
    bool aBoolean  = false; 
    JMLib::float32 aFloat32  = 8; 
    JMLib::float64 aFloat64  = 9; 

    aPacket << aStr;
    JMLib::string aOutString;
    aPacket >> aOutString;
    EXPECT_STREQ( aStr.c_str(), aOutString.c_str());

    aPacket << aUint8;
    JMLib::uint8 aUint8Out;
    aPacket >> aUint8Out;
    EXPECT_EQ( aUint8, aUint8Out );
}