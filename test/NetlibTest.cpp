#include <gtest/gtest.h>
#include "SysPacket.h"
#include "SendPacket.h"
#include "RecvPacket.h"
#include "NetworkException.h"
#include "ServerEPoll.h"
#include "CommSocketEPoll.h"
#include "ListenSocketEPoll.h"

TEST( NetLibTest, PacketTest )
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



    JMLib::NetLib::CSendPacket aPacket3( 75, 48 );
    EXPECT_EQ( aPacket3.Owner(), 75);
    EXPECT_EQ( aPacket3.Command(), 48);
    EXPECT_EQ( aPacket3.Size(), 6);

    for( int i = 0; i < 1022; i ++ ) {
        aPacket3 << (JMLib::int32) i ;
    }
    
    EXPECT_THROW( aPacket3 << (JMLib::int32) 2032, JMLib::NetLib::CNetworkException );
    EXPECT_THROW( aPacket3 << (JMLib::int32) 2032, JMLib::NetLib::CNetworkException );
}

TEST( NetLibTest, SendPacket )
{
    JMLib::NetLib::CSendPacket aPacket( 75, 17 );
    aPacket << (JMLib::uint32) 32 << (JMLib::uint16) 745;

    char * pBuffer = aPacket.GetBuffer();
    JMLib::uint16 aIDentifier = 0;
    memcpy( &aIDentifier, pBuffer, sizeof( JMLib::uint16 ));
    EXPECT_EQ( aIDentifier, JMLib::NetLib::DPACKET_IDENTIFIER );
    JMLib::uint16 aCommand = 0;
    memcpy( &aCommand, pBuffer + sizeof(JMLib::uint16), sizeof(JMLib::uint16));
    EXPECT_EQ( aCommand, 17 );
    JMLib::uint16 aSize = 0;
    JMLib::uint16 aExpSize = JMLib::NetLib::DHEADER_SIZE + sizeof(JMLib::uint16) + sizeof(JMLib::uint32);
    memcpy( &aSize, pBuffer + sizeof(JMLib::uint16) * 2, sizeof( JMLib::uint16));
    EXPECT_EQ( aSize, aExpSize);

    aPacket << (JMLib::float32) 0.14 ;
    aExpSize += sizeof( JMLib::float32 );
    memcpy( &aSize, pBuffer + sizeof(JMLib::uint16) * 2, sizeof( JMLib::uint16));
    EXPECT_NE( aSize, aExpSize );           // 아직 size변경이 적용되지 않았다. 

    char * pBuffer2 = aPacket.GetBuffer();  // size변경이 이때 적용된다. 
    EXPECT_EQ( pBuffer, pBuffer2 );         //! pointer 의 주소는 같다. 
    memcpy( &aSize, pBuffer + sizeof(JMLib::uint16) * 2, sizeof( JMLib::uint16));
    EXPECT_EQ( aSize, aExpSize );           // 이제 같아야 한다. 
}

TEST( NetLibTest, RecvPacket )
{
    JMLib::NetLib::CSendPacket aPacket( 75, 17 );
    aPacket << (JMLib::uint32) 32 << (JMLib::uint16) 745;
    JMLib::string aStr = L"손잡고 가보자 같이 가보자!";
    aPacket << aStr;

    JMLib::NetLib::CRecvPacket aRecv( 75 );
    memcpy( aRecv.GetBuffer(), aPacket.GetBuffer(), aPacket.Size());
    JMLib::uint32 aOut1;
    EXPECT_EQ( aRecv.Owner(), 75 );
    EXPECT_NE( aRecv.Size(), aPacket.Size() );
    EXPECT_THROW( aRecv >> aOut1, JMLib::NetLib::CNetworkException );
    EXPECT_NE( aRecv.Command(), 17 );

    JMLib::int32 aSize = aPacket.Size();
    aRecv.SetRead( aSize );

    char * pBuffer = aRecv.GetBuffer();
    JMLib::uint16 aIDentifier = 0;
    memcpy( &aIDentifier, pBuffer, sizeof( JMLib::uint16 ));
    EXPECT_EQ( aIDentifier, JMLib::NetLib::DPACKET_IDENTIFIER );
    JMLib::uint16 aCommand = 0;
    memcpy( &aCommand, pBuffer + sizeof(JMLib::uint16), sizeof(JMLib::uint16));
    EXPECT_EQ( aCommand, 17 );
    JMLib::string aOutString;
    JMLib::uint16 aOut2;
    aRecv >> aOut1 >> aOut2 >> aOutString;
    EXPECT_EQ( aOut1, 32 );
    EXPECT_EQ( aOut2, 745 );
    EXPECT_STREQ( aStr.c_str(), aOutString.c_str() );
}

TEST( NetLibTest, SysPacket )
{
    EXPECT_THROW( JMLib::NetLib::CSysPacket aPacket( 32, 14 ), JMLib::NetLib::CNetworkException );
    JMLib::NetLib::CSysPacket aSysPacket1( 335, JMLib::Packet::Sys::DCONNECT );
    JMLib::string aStr = L"우리들이 함께 있는밤";
    EXPECT_THROW( aSysPacket1 << (JMLib::uint32 ) 32, JMLib::NetLib::CNetworkException );
    EXPECT_THROW( aSysPacket1.GetBuffer(), JMLib::NetLib::CNetworkException );
    JMLib::float64 aOutVal;
    EXPECT_THROW( aSysPacket1 >> aOutVal, JMLib::NetLib::CNetworkException );
    EXPECT_THROW( aSysPacket1 << aStr, JMLib::NetLib::CNetworkException );
    EXPECT_EQ( aSysPacket1.Owner(), 335 );
    EXPECT_EQ( aSysPacket1.Command(), JMLib::Packet::Sys::DCONNECT );
    EXPECT_EQ( aSysPacket1.Size(), JMLib::NetLib::DHEADER_SIZE );
}

class CListenerMock : public JMLib::NetLib::CListenSocketEPoll
{
    public:
    CListenerMock( JMLib::NetLib::CServerEPoll & irServer, JMLib::ICallback & irCallback)
        : JMLib::NetLib::CListenSocketEPoll( irServer, irCallback ) {}
    ~CListenerMock() {}

    JMLib::int32 OnEvent() const 
    {
        std::shared_ptr<JMLib::NetLib::CCommSocketEPoll> aClientSock 
            = std::make_shared<JMLib::NetLib::CCommSocketEPoll>( mrCallback );
        EXPECT_THROW( aClientSock->Init( 10, 54352, 321324 ), JMLib::NetLib::CNetworkException );
        OnAccept( aClientSock );
        return 0;
    }

};

//! EPoll Server test용 class 
class CServerEPollMock : public JMLib::NetLib::CServerEPoll
{
    public:
    JMLib::NetLib::esock maListenerSock;
    public:
    CServerEPollMock() {}
    ~CServerEPollMock() {}

    int GetSize() { return maSockets.size(); }
    JMLib::NetLib::fd GetEPollFD() {  return maEPollFD; }

    JMLib::NetLib::esock CreateListener( 
        const JMLib::NetLib::port iaPort, JMLib::ICallback & irCallBack ) 
    {
        std::shared_ptr<CListenerMock> aSock = std::make_shared< CListenerMock > ( *this, irCallBack );
        aSock->Init( iaPort );
        maListenerSock = aSock;
        return maListenerSock;
    }

    void InsertSock( JMLib::NetLib::esock iaSock ) 
    {
        maSockets.emplace( iaSock->GetFD(), iaSock );
    }
};

TEST( NetLibTest, EPollServer )
{
    CServerEPollMock aServer;
    JMLib::ICallback aCallback =  [] ( const JMLib::IPacket & irPacket ) -> JMLib::int32 {
        EXPECT_EQ( irPacket.Command() , JMLib::Packet::Sys::DCONNECT );
        EXPECT_EQ( irPacket.Owner(), 10 );
        EXPECT_EQ( irPacket.Size(), JMLib::NetLib::DHEADER_SIZE );
        return 0;
    };
    EXPECT_EQ( aServer.GetEPollFD(), 0 );
    EXPECT_EQ( aServer.maListenerSock.use_count(), 0 );
    EXPECT_EQ( aServer.GetSize(), 0 );
    EXPECT_TRUE( aServer.Init( 6523, aCallback ) );
    EXPECT_NE( aServer.GetEPollFD(), 0 );
    EXPECT_NE( aServer.maListenerSock->GetFD(), 0 );
    EXPECT_EQ( aServer.GetSize(), 1 );

    aServer.maListenerSock->OnEvent();
    EXPECT_EQ( aServer.GetSize(), 2 );

    JMLib::NetLib::CSendPacket aPack1( 75, 48 );
    EXPECT_TRUE( aServer.Send( aPack1 ) < 0 );

    //! Connect모사해 본다. 
    //Check Sockets는. 테스트 가능한가? 
    //! Send Test 해본다. 예외상황 정확히 발생을 하는지. 
    //! Listener에게 send 해본다. 
    //! CommSock에 Send 해본다. 
}