#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "ListenSocketEPoll.h"
#include "NetworkException.h"

using namespace JMLib::NetLib;

CListenSocketEPoll::CListenSocketEPoll( const IServer & irServer ) 
    : maListenFD( 0 ), mrServer( irServer )
{
}

CListenSocketEPoll::~CListenSocketEPoll()
{
    if( maListenFD != 0 )
        close( maListenFD );
}

void CListenSocketEPoll::Init( const uint16 iaPort )
{
    try {
        Create();
        Bind();
        Listen();
    } 
    catch( CNetworkException e ) {
        if( maListenFD !=  0 )
            close( maListenFD )
        throw e;
    }
}

const fd CListenSocketEPoll::GetFD() const
{
    return maListenFD;
}

void CListenSocketEPoll::Close() 
{
    if( maListenFD == 0 )
        return;
    close( maListenFD );
}

void CListenSocketEPoll::Create()
{
    maListenFD = socket( PF_INET, SOCK_STREAM, 0 );
    if( maListenFD < 1 )
        throw CNetworkException( NError::NLevel::DERROR, L"socket() fuction Fail" );

    int32 aFlag = fcntl( maListenFD, F_GETFL );
    aFlag |= O_NONBLOCK;
    int aRet = fcntl( maListenFD, F_SETFL, aFlag );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"fcntl() fuction Fail" );
    int32 aOption = true;
    aRet = setsockopt( maListenFD, SOL_SOCKET, SO_REUSEADDR, &aOption, sizeof(aOption) );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"setsockopt() fuction Fail" );
}

void CListenSocketEPoll::Bind()
{
    struct sockaddr_in aServerAddr;
    bzero( &aServerAddr, sizeof(aServerAddr));
    aServerAddr.sin_family = AF_INET;
    aServerAddr.sin_addr.s_addr = htonl( INADDR_ANY);
    aServerAddr.sin_port = htons( iaPort );
    int aRet = bind( maListenFD, (struct sockaddr * ) &aServerAddr, sizeof(aServerAddr) );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"bind() fuction Fail" );
}

void CListenSocketEPoll::Listen()
{
    int aRet = listen(maListenFD, DMAX_BACKLOG );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"listen() function fail");
}