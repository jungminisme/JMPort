#include "NetworkManager.h"
#include "LogManager.h"
#include "ServerEPoll.h"

using namespace JMLib::NetLib;

CNetworkManager & CNetworkManager::GetInstance() 
{
    static CNetworkManager aInstance;
    return aInstance;
}

bool CNetworkManager::Init( const uint8 iaPort, const ICallback & irCallback ) 
{
    if( mpServer.use_count() == 0 ) {
        mpServer = std::make_shared< CServerEPoll > ();
        CLogManager & aLM = CLogManager::GetInstance();
        aLM.AddLogger( L"netlib", JMLib::NLog::NType::DCONSOLE, JMLib::NLog::NLevel::DALL );
    }
    return mpServer->Init( iaPort, irCallback );
}

JMLib::int32 CNetworkManager::Send( const IPacket & irPacket ) const
{
    return 0;
}