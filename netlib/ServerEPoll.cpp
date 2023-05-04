#include "ServerEPoll.h"
#include "NetworkException.h"
#include "ILogger.h"
#include "ListenSocketEPoll.h"
#include <sys/epoll.h>
#include <unistd.h>

using namespace JMLib::NetLib;

/**
 * @brief Construct a new CServerEPoll::CServerEPoll object
 * 소멸시를 대비하여 maEPollFD를 초기화 한다. 
 */
CServerEPoll::CServerEPoll() :  maEPollFD( 0 )
{

}

/**
 * @brief Destroy the CServerEPoll::CServerEPoll object
 * maSockets를 비워 전체 소켓을 삭제 한다. 소켓들은 지들이 알아서 fd를 close한다. 
 * 자기가 직접 가지고 있는 maEPollFD도 close한다. 
 */
CServerEPoll::~CServerEPoll()
{
    maSockets.clear();
    if( maEPollFD != 0 )
        close(maEPollFD);
}

/**
 * @brief Epoll 방식으로 서버를 가동한다. 
 * multiplexing은 epoll 로 하고, 자기 thread에서 계속 읽는다. 
 * 읽는 것이 완료 되었을때 callback->Post를 호출한다. 
 * 
 * @param iaPort 포트 번호
 * @param irCallback data가 receive되거나 connect, disconnect가 되었을때의 동작 콜백
 * @return true 서버 시작 성공
 * @return false 서버 시작 실패
 */
bool CServerEPoll::Init( const port iaPort, ICallback & irCallback ) 
{
    try {
        CreateEPoll( CreateListener( iaPort, irCallback ) );
    }
    catch( CNetworkException const & e ) {
        LOG_ERROR( L"netlib", e.GetErrorMessage().c_str() );
        return false;
    }
    return true;
}

/**
 * @brief Packet을 전송한다. 어디에 전송할지는 Packet이 가지고 있는 거로 하자. 
 * 패킷이 가지고 있는 주소의 socket이 없다면 안보낸다. 
 * @param irPacket 보내질 패킷
 * @return JMLib::int32 보내진 데이터 양, 소켓이 없다면 -1
 */
JMLib::int32 CServerEPoll::Send( IPacket & irPacket ) const
{
    int32 aKey = irPacket.Owner();
    auto aIt =  maSockets.find( aKey );
    if( aIt == maSockets.end() )
        return -1;
    esock aSock = aIt->second;
    return aSock->Send(irPacket);
}

/**
 * @brief 새로운 socket이 추가 되었다. 
 * InsertSock에 모든 작업을 맡긴다. 
 * @param iaSock 추가될 socket
 */
void JMLib::NetLib::CServerEPoll::OnConnect(esock iaSock)
{
    InsertSock( iaSock );
}

/**
 * @brief Socket들의 상태를 체크 한다. 정확히는 epoll에서 event발생하는 것을 wait한다. 
 * 전통적인 방법은 milli sec를 주고 기다리는 것. 
 * 비동기식으로 간다면. 여기서 또 thread를 사용해야 한다. 
 * 이벤트가 발생하면 socket을 찾아서, OnEvent를 날린다. 
 * OnEvent에 대한 행동은 socket들이 알아서 잘하게 한다. 
 * @return int32 발견된 event의 갯수, listener가 망가지는등 sever가 동작 못하면 -1
 */
JMLib::int32 JMLib::NetLib::CServerEPoll::CheckSockets()
{
    struct epoll_event aEvents[DMAX_EPOLL_EVENT];
    int32 aEventCount = 0;
    aEventCount = epoll_wait( maEPollFD, aEvents, DMAX_EPOLL_EVENT, DEPOLL_TIME_OUT);
    if( aEventCount < 0 ) {
        string aErrString;
        aErrString.StrToWstr( std::string( strerror(errno)));
        throw CNetworkException( NError::NLevel::DERROR, aErrString );
    }
    for( int i = 0; i < aEventCount; i++ ) {
        fd aFD = aEvents[i].data.fd;
        auto aIT = maSockets.find( aFD );
        if( aIT == maSockets.end() ) 
            continue;
        esock aCurSock = aIT->second;
        aCurSock->OnEvent();
    }
    return 0;
}

/**
 * @brief io multiplexing을 위한 epoll fd를 생성한다. 
 * Listener가 생성되었다고 알려오면, 그때 생성해야 해서 구조가 좀 그렇다. 
 * @param iaListener accept를 대기할 server socket
 */
void CServerEPoll::CreateEPoll( esock iaListener )
{
    maEPollFD = epoll_create(1);
    if( maEPollFD < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"epoll_create() error");
    InsertSock( iaListener );
}

/**
 * @brief Server에 socket을 추가한다. 
 * map에 추가한 후에, epoll 객체에 수신을 대기 시켜 놓는다. 
 * @param iaSock 추가할 socket 
 */
void CServerEPoll::InsertSock( esock iaSock )
{
    maSockets.emplace( iaSock->GetFD(), iaSock );
    struct epoll_event aEvent;
    aEvent.events = EPOLLIN | EPOLLET;
    aEvent.data.fd = iaSock->GetFD();
    if( epoll_ctl( maEPollFD, EPOLL_CTL_ADD, iaSock->GetFD(), &aEvent ) < 0 ) 
        throw CNetworkException( NError::NLevel::DERROR, L"epoll_ctl() error");
}

/**
 * @brief ListenerSocket을 생성하고 초기화 한다. 
 * 
 * @param iaPort Listen 소켓의 포트 번호
 * @param irCallback callback 
 * @return JMLib::NetLib::esock 생성된 소켓 
 */
JMLib::NetLib::esock CServerEPoll::CreateListener(const port iaPort, ICallback & irCallback)
{
    std::shared_ptr<CListenSocketEPoll> aListener 
        = std::make_shared<CListenSocketEPoll>( *this, irCallback );
    aListener->Init( iaPort );
    return aListener;
}
