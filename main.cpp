#include <iostream>
#include "JMString.h"
#include "NetworkManager.h"
#include "NetworkException.h"
#include "LogManager.h"
#include "DBManager.h"
#include "SendPacket.h"

using namespace JMLib;

void InitLauncher( CActionLauncher & irLauncher );

int main(int, char**) 
{
    CActionLauncher aLauncher;
    InitLauncher( aLauncher );
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.AddLogger(L"server", NLog::NType::DCONSOLE );
    aLM.SetDefaultChannel( L"server" );

    DBLib::CDBManager & rDBM = DBLib::CDBManager::GetInstance();
    if( rDBM.Connect(L"tcp://127.0.0.1:3306",L"db_master", L"master", L"account" ) == false )
        return -1;

    NetLib::CNetworkManager & aNM = NetLib::CNetworkManager::GetInstance();
    try {
        aNM.Init(1536, aLauncher );
    } catch ( NetLib::CNetworkException e ) {
        LOG_ERROR_D( e.GetErrorMessage().c_str() );
    }
    return 0;
}

void InitLauncher( CActionLauncher & irLauncher )
{
    ICallback aCallback = [] ( IPacket & irPacket ) -> int32 {
        if( irPacket.Command() >= Packet::Sys::DSYS_START ) {
            LOG_INFO_D( L"Owner : %d Command : %d ", irPacket.Owner(), irPacket.Command());
            return 0;
        }
        NetLib::CNetworkManager & rNM = NetLib::CNetworkManager::GetInstance();

        switch( irPacket.Command() ) {
            case 1: {
                string aID;
                string aPass;
                irPacket >> aID >> aPass;
                NetLib::CSendPacket aPacket( irPacket.Owner(), irPacket.Command() );

                DBLib::CDBManager & rDBM = DBLib::CDBManager::GetInstance();
                string aQeury;
                aQeury.Format( L"SELECT account_id, nick FROM ACCOUNT WHERE ID = %S AND PASS = %S", aID.c_str(), aPass.c_str() );
                DBLib::result aResult = rDBM.ExecuteStatement( aQeury );
                if( aResult.use_count() < 1 ) {
                    NetLib::CSendPacket aPacket( irPacket.Owner(), irPacket.Command() );
                    aPacket << false;
                    rNM.Send( aPacket );
                    return 0;
                }
                aPacket << true;
                uint32 aAID = aResult->GetUInt(0);
                string aNick = aResult->GetString(1);
                
                rNM.Send( aPacket );
                return 0;
            }
            break;
            case 2: {
                return 0;
            }
            break;
            default:
                return 0;
        }
        return 0;
    };
    irLauncher.Regist( 1, aCallback );
}