#include "NetworkManager.h"
#include "LogManager.h"
#include "ServerEPoll.h"

using namespace JMLib::NetLib;

CNetworkManager::CNetworkManager() 
{
    mpServer = std::make_shared< CServerEPoll > ();
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.AddLogger( L"netlib", JMLib::NLog::NType::DCONSOLE, JMLib::NLog::NLevel::DALL );
}

CNetworkManager & CNetworkManager::GetInstance() 
{
    static CNetworkManager aInstance;
    return aInstance;
}

bool CNetworkManager::Init( const uint16 iaPort, const ICallback & irCallback ) 
{
    return mpServer->Init( iaPort, irCallback );
}

JMLib::int32 CNetworkManager::Send( const IPacket & irPacket ) const
{
    return mpServer->Send( irPacket );
}