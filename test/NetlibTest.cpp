#include <gtest/gtest.h>
#include "SysPacket.h"
#include "SendPacket.h"
#include "NetworkException.h"

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

    aPacket << aUint16;
    JMLib::uint16 aUint16Out;
    aPacket >> aUint16Out;
    EXPECT_EQ( aUint16, aUint16Out );

    aPacket << aUint32;
    JMLib::uint32 aUint32Out;
    aPacket >> aUint32Out;
    EXPECT_EQ( aUint32, aUint32Out );

    aPacket << aInt8;
    JMLib::int8 aInt8Out;
    aPacket >> aInt8Out;
    EXPECT_EQ( aInt8, aInt8Out );

    aPacket << aInt16;
    JMLib::int16 aInt16Out;
    aPacket >> aInt16Out;
    EXPECT_EQ( aInt16, aInt16Out );

    aPacket << aInt32;
    JMLib::int32 aInt32Out;
    aPacket >> aInt32Out;
    EXPECT_EQ( aInt32, aInt32Out );

    aPacket << aBoolean;
    bool aBooleanOut;
    aPacket >> aBooleanOut;
    EXPECT_EQ( aBoolean, aBooleanOut );

    aPacket << aFloat32;
    JMLib::float32 aFloat32Out;
    aPacket >> aFloat32Out;
    EXPECT_EQ( aFloat32, aFloat32Out);

    aPacket << aFloat64;
    JMLib::float64 aFloat64Out;
    aPacket >> aFloat64Out;
    EXPECT_EQ( aFloat64, aFloat64Out);
    EXPECT_THROW( aPacket >> aFloat64Out, JMLib::NetLib::CNetworkException );

    JMLib::NetLib::CSendPacket aPacket2( 12, 32 );
    EXPECT_EQ( aPacket2.Owner(), 12);
    EXPECT_EQ( aPacket2.Command(), 32);
    EXPECT_EQ( aPacket2.Size(), 6);

    aPacket2 << aStr << aUint8 << aUint16 << aUint32 << aInt8 << aInt16 << aInt32;
    aPacket2 << aBoolean << aFloat32 << aFloat64;

    aPacket2 >> aOutString >> aUint8Out >> aUint16Out >> aUint32Out >> aInt8Out;
    aPacket2 >> aInt16Out >> aInt32Out >> aBooleanOut >> aFloat32Out >> aFloat64Out;

    EXPECT_STREQ( aStr.c_str(), aOutString.c_str() );
    EXPECT_EQ( aUint8, aUint8Out );
    EXPECT_EQ( aUint16, aUint16Out );
    EXPECT_EQ( aUint32, aUint32Out );
    EXPECT_EQ( aInt8, aInt8Out );
    EXPECT_EQ( aInt16, aInt16Out );
    EXPECT_EQ( aInt32, aInt32Out );
    EXPECT_EQ( aBoolean, aBooleanOut );
    EXPECT_EQ( aFloat32, aFloat32Out );
    EXPECT_EQ( aFloat64, aFloat64Out );
}