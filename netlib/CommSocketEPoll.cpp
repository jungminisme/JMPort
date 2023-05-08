#include <unistd.h>
#include <fcntl.h>
#include "CommSocketEPoll.h"
#include "NetworkException.h"
#include "RecvPacket.h"
#include "SysPacket.h"
#include "ServerEPoll.h"

using namespace JMLib::NetLib;

CCommSocketEPoll::CCommSocketEPoll( ICallback & irCallback, CServerEPoll & irServer ) 
    : CSocketEPoll( irCallback ), mrServer( irServer )
{
}

CCommSocketEPoll::~CCommSocketEPoll()
{
}

/**
 * @brief 클라이언트 socket의 상태 변화가 감지됨. 
 * 상태 변화는 두가지 
 * 1. socket에 data가 들어왔을때. 읽어서 callback에 Packet을 날린다. 
 * 2. socket의 연결이 끊어졌을때. CSocketClosePacket을 생성해 callback에 알리고, 
 * NetworkManager 에게 소켓 삭제를 요청한다. 
 * //TODO 이때도 thread pooling을 하는게 좋다. 읽는데 생각보다 시간이 많이 걸린다. 
 * // 다 읽고 나서 완료처리까지 해주는 IOCP가 그래서 좋다. 
 * @return JMLib::int32 data를 읽은 경우 읽은 양, 끊어진 경우 0, 에러인경우 음수
 */
JMLib::int32 CCommSocketEPoll::OnEvent() 
{
    CRecvPacket aPacket(maFD);
    //! 우선 읽어 본다. 
    int aReadSize = read( maFD, aPacket.GetBuffer(), DMAX_PACKET_SIZE );
    if( aReadSize == 0 ) {      //! 연결이 끊어짐
        OnClose();
        return 0;
    }
    if( aReadSize < 0 ) {       //! 에러가 발생함
        onRecvError();
        return aReadSize;
    }
    aPacket.SetRead(aReadSize);
    int aSizeToRead = (int) aPacket.Size();
    while( aReadSize < aSizeToRead ) {      //! 읽은양이 읽어야할 양보다 작은경우 
        int aRemain = aSizeToRead - aReadSize;
        //! 다시 읽는다. 
        int aTemp = read( maFD, aPacket.GetBuffer() + aReadSize, aRemain );
        if( aTemp == 0 ) {      //! 다시 읽는중 끊어짐
            OnClose();
            return 0;
        }
        if( aTemp < 0 ) {       //! 다시 읽는중 에러발생
            onRecvError();
            return aTemp;
        }
        aReadSize += aTemp;
    }
    mrCallback( aPacket ); //! 읽은 패킷을 Callback 에 전달한다. 
    return (int32) aPacket.Size();
}

/**
 * @brief 클라이언트로 Data를 전송하는 부분 
 * 패킷의 사이즈보다 보내진 양이 적다면. 다 보내질때까지 계속 보낸다. 
 * //TODO : 이후 이부분에 thread pooling을 한다. 보내는 건 오래 걸리는 일이다. 
 * @param irPacket 전송할 패킷 정보
 * @return JMLib::int32 전송된 Data의 양 . 
 */
JMLib::int32 CCommSocketEPoll::Send( IPacket &irPacket) const
{
    int aSizeToWrite = (int) irPacket.Size();
    int aWriteCount = write( maFD, irPacket.GetBuffer(), aSizeToWrite );
    if( aWriteCount < 0 ) {
        string aErrString;
        aErrString.StrToWstr( strerror( errno ) );
        throw CNetworkException( NError::NLevel::DERROR, aErrString );
    }
    int aRetryCount = 0;
    //! 최대 5번까지만 write 해본다. 에러는 아니지만 0바이트를 적는 경우가 있다. 
    while(  aWriteCount < aSizeToWrite ) { 
        int aRemain = aSizeToWrite - aWriteCount;
        int aRet = write( maFD, irPacket.GetBuffer() + aWriteCount, aRemain );
        if( aRet < 0 ) {
            string aErrString;
            aErrString.StrToWstr( strerror( errno ) );
            throw CNetworkException( NError::NLevel::DERROR, aErrString );
        }
        aWriteCount += aRet;
        aRetryCount++;
        if( aRetryCount >= 4 ) {
            throw CNetworkException( NError::NLevel::DERROR, L"Write retry cout over!" );
        }
    }
    return aWriteCount;
}

/**
 * @brief Accept때 받은 정보를 socket을 초기화 한다. 
 * 기본 변수를 받아 오는 것 외에, fd를 NON_BLOCK으로 바꾼다. 
 * 
 * @param iaFD 접속된 File의 Descriptor 이것으로 통신한다.
 * @param iaPort 포트 번호. 부가 정보이다. 사실 쓸데는 없음.
 * @param iaAddr 상대방의 IP주소, 공용주소만 알수 있다. 사설주소는 거꾸로 client에서 받아야함
 */
void CCommSocketEPoll::Init( fd iaFD, port iaPort, uint32 iaAddr )
{
    maFD = iaFD;
    maPort = iaPort;
    maPublicAddr = iaAddr;
    int32 aFlag = fcntl( maFD, F_GETFL );
    aFlag |= O_NONBLOCK;
    int aRet = fcntl( maFD, F_SETFL, aFlag );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"fcntl() fuction Fail" );
}

/**
 * @brief Socket Close를 처리 한다. 
 * FD를 close 하고, Server로부터 Socket Object를 제거 하도록 한다. 
 */
void CCommSocketEPoll::OnClose()
{
    mrServer.OnClose( maFD );
    CSysPacket aPack( maFD, Packet::Sys::DCLOSE );
    mrCallback( aPack );
    Close();
}

void CCommSocketEPoll::onRecvError() const
{
    CSysPacket aPack( maFD, Packet::Sys::DERROR );
    mrCallback( aPack );
}
