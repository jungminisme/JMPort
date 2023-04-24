#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include "ListenSocketEPoll.h"
#include "NetworkException.h"
#include "CommSocketEPoll.h"

using namespace JMLib::NetLib;

/**
 * @brief Construct a new CListenSocketEPoll::CListenSocketEPoll object
 * 중요 member의 null 방지를 위해 생성자에서 모든 인자를 받는다. 
 * accept가 발생했을때 socket을 추가해줘야 하기에 server객체를 받는다. 
 * NetworkManager를 받기에는 EPollSocket을 외부로 알리고 싶지 않아서 
 * CServerEPoll로 class 정보가 퍼지는 것을 막는다. 
 * 
 * @param irServer connet시 호출될 server객체
 * @param irCallback callback은 client에게 초기화를 위해 받아 둔다. 
 */
CListenSocketEPoll::CListenSocketEPoll( CServerEPoll & irServer, ICallback & irCallback ) 
    :  CSocketEPoll(irCallback), mrServer( irServer )
{
}

CListenSocketEPoll::~CListenSocketEPoll()
{
}

/**
 * @brief 소켓을 생성하고 connect대기 상태까지 만들어 둔다. 
 * 한 함수에서 처리하기에 소스가 좀 길어서 내부에서 함수를 나누어 둔다. 
 * @param iaPort 포트 번호
 */
void CListenSocketEPoll::Init( const port iaPort )
{
    try {
        Create();
        Bind( iaPort );
        Listen();
    } 
    catch( CNetworkException const & e ) {
        Close();
        throw e;
    }
}

/**
 * @brief EPoll에 의해 socket fd의 변화가 감지 되었을때의 함수
 * Listener socket은 fd변화시에 accept말고는 할게 없다. 
 * accept한 후, commsocket을 만들어 초기화 해주고, 
 * server에 연결되었음을 알려준다. 
 * @return JMLib::int32 0을 반환한다. 에러의 경우 exception을 날린다. 
 */
JMLib::int32 CListenSocketEPoll::OnEvent() const
{
    int32 aClientFD = 0;
    struct sockaddr_in aClientAddr;
    int32 aClientLength = sizeof(aClientAddr);
    aClientFD = accept( maFD, ( sockaddr * ) &aClientAddr, (socklen_t *) &aClientLength);
    if( aClientFD < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"accept() fuction Fail" );
    std::shared_ptr<CCommSocketEPoll> aClientSock = std::make_shared<CCommSocketEPoll>( mrCallback );
    aClientSock->Init( aClientFD );
    mrServer.OnConnect( aClientSock );
    return 0;
}

/**
 * @brief 이것은 호출되면 안될 함수
 * SocketEPoll을 위해 Send가 마련되어 있지만. Listener소켓에게 이 함수가 호출되면 에러다. 
 * @param irPacket 전송될 패킷. 무시된다. 
 * @return JMLib::int32 -1 반환. 그전에 exception이 날라가므로 의미 없다. 
 */
JMLib::int32 CListenSocketEPoll::Send(const IPacket &irPacket) const
{
    throw CNetworkException( NError::NLevel::DWARN, L"You sent data to Listen socket");
    return -1;
}

/**
 * @brief Listen을 위한 socket을 생성한다. 
 * 생성 후에는 NON_BLOCK으로 상태를 변경하고, SO_REUSEADDR로 옵션으로 준다. 
 */
void CListenSocketEPoll::Create()
{
    maFD = socket( PF_INET, SOCK_STREAM, 0 );
    if( maFD < 1 )
        throw CNetworkException( NError::NLevel::DERROR, L"socket() fuction Fail" );

    int32 aFlag = fcntl( maFD, F_GETFL );
    aFlag |= O_NONBLOCK;
    int aRet = fcntl( maFD, F_SETFL, aFlag );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"fcntl() fuction Fail" );
    int32 aOption = true;
    aRet = setsockopt( maFD, SOL_SOCKET, SO_REUSEADDR, &aOption, sizeof(aOption) );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"setsockopt() fuction Fail" );
}

/**
 * @brief Port 번호에 맞게 socket을 binding한다. 
 * 
 * @param iaPort 포트 번호
 */
void CListenSocketEPoll::Bind( const port iaPort )
{
    struct sockaddr_in aServerAddr;
    bzero( &aServerAddr, sizeof(aServerAddr));
    aServerAddr.sin_family = AF_INET;
    aServerAddr.sin_addr.s_addr = htonl( INADDR_ANY);
    aServerAddr.sin_port = htons( iaPort );
    int aRet = bind( maFD, (struct sockaddr * ) &aServerAddr, sizeof(aServerAddr) );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"bind() fuction Fail" );
}

/**
 * @brief socket을 응답 대기 모드로 만든다. 
 * 
 */
void CListenSocketEPoll::Listen()
{
    int aRet = listen( maFD, DMAX_BACKLOG );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"listen() function fail");
}