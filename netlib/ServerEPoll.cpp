#include "ServerEPoll.h"
#include "NetworkException.h"
#include "ILogger.h"


using namespace JMLib::NetLib;

CServerEPoll::CServerEPoll() : maListener( * this )
{

}

CServerEPoll::~CServerEPoll()
{
    maListener.Close();
}

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
    try {
        maListener.Init( iaPort );
    }
    catch( CNetworkException const & e ) {
        LOG_ERROR( L"netlib", e.GetErrorMessage().c_str() );
        return false;
    }
    return true;
}

JMLib::int32 CServerEPoll::Send( const IPacket & irPacket ) const
{
    return 0;
}