#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "ServerEPoll.h"
#include "NetworkException.h"


using namespace JMLib::NetLib;

/**
 * @brief Epoll 방식으로 서버를 가동한다. 
 * multiplexing은 epoll 로 하고, 자기 thread에서 계속 읽는다. 
 * 읽는 것이 완료 되었을때 callback->Post를 호출한다. 
 * 
 * @param iaPort 포트 번호
 * @param irCallback data가 recve되거나 connect, disconnect가 되었을때의 동작 콜백
 * @return true 서버 시작 성공
 * @return false 서버 시작 실패
 */
bool CServerEPoll::Init( const uint16 iaPort, const ICallback & irCallback ) 
{
    maListenFD = socket(AF_INET, SOCK_STREAM, 0 );
    if( maListenFD < 1 )
        throw CNetworkException( NError::NLevel::DERROR, L"socket() fuction Fail" );
    struct sockaddr_in aServerAddr;
    bzero( &aServerAddr, sizeof(aServerAddr));
    aServerAddr.sin_family = AF_INET;
    aServerAddr.sin_addr.s_addr = htonl( INADDR_ANY);
    aServerAddr.sin_port = htons( iaPort );
    int aRet = bind( maListenFD, (struct sockaddr * ) &aServerAddr, sizeof(aServerAddr) );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"bind() fuction Fail" );
    aRet = listen(maListenFD, DMAX_BACKLOG );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"listen() function fail");
    return true;
}

JMLib::int32 CServerEPoll::Send( const IPacket & irPacket ) const
{
    return 0;
}