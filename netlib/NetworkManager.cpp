#include "NetworkManager.h"
#include "LogManager.h"
#include "ServerEPoll.h"

using namespace JMLib::NetLib;

/**
 * @brief Construct a new CNetworkManager::CNetworkManager object
 * 내부에 server를 생성하고, Logger를 세팅한다. 
 */
CNetworkManager::CNetworkManager() 
{
    mpServer = std::make_shared< CServerEPoll > ();
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.AddLogger( L"netlib", JMLib::NLog::NType::DCONSOLE, JMLib::NLog::NLevel::DALL );
}

/**
 * @brief singleton 함수
 * 
 * @return CNetworkManager& 
 */
CNetworkManager & CNetworkManager::GetInstance() 
{
    static CNetworkManager aInstance;
    return aInstance;
}

/**
 * @brief 주어진 port로 서버를 기동한다. 
 * packet전달을 위해서 callback을 전달 받는데. 실제 동작 내용을 callback으로 전달받지 않으면
 * 모든 구현이 network 에서 이루어 지는 수가 있다. 
 * 아니면 network의 모든 구현이 contents쪽으로 들어가버리는 경우가 있어 복잡해진다. 
 * contents 와 library를 구분하기 위한 격벽으로 callback과 Interface를 둔다. 
 * @param iaPort open할 port번호
 * @param irCallback 외부와의 interface를 위한 callback
 * @return true 서버가 기동되어 외부 접속을 기다림. 
 * @return false 서버 기동 실패
 */
bool CNetworkManager::Init( const port iaPort, ICallback & irCallback ) 
{
    return mpServer->Init( iaPort, irCallback );
}

/**
 * @brief 패킷의 정보를 client로 전송한다. 
 * 
 * @param irPacket 전송할 패킷
 * @return JMLib::int32 전송된 data의 양
 */
JMLib::int32 CNetworkManager::Send( const IPacket & irPacket ) const
{
    return mpServer->Send( irPacket );
}