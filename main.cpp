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
    if( rDBM.Connect(L"tcp://192.168.35.203:3306",L"db_master", L"master", L"account_db" ) == false )
        return -1;

    NetLib::CNetworkManager & aNM = NetLib::CNetworkManager::GetInstance();
    aNM.Init(1536, aLauncher );
    while(1) {
        try {
                aNM.Run( -1 );
        } catch ( NetLib::CNetworkException e ) {
            LOG_ERROR_D( e.GetErrorMessage().c_str() );
        }
    }
    return 0;
}

void InitLauncher( CActionLauncher & irLauncher )
{
    irLauncher.Regist( Packet::Sys::DCONNECT, [] (IPacket & irPacket ) -> int32 {
            LOG_INFO_D( L"Owner : %d Connected", irPacket.Owner() );
            return 0;
    } );
    irLauncher.Regist( Packet::Sys::DCLOSE, [] (IPacket & irPacket ) -> int32 {
            LOG_INFO_D( L"Owner : %d Disconnected ", irPacket.Owner());
            return 0;
    } );
    irLauncher.Regist( Packet::Sys::DERROR, [] (IPacket & irPacket ) -> int32 {
            LOG_INFO_D( L"Owner : %d Error Find ", irPacket.Owner());
            return 0;
    } );

    irLauncher.Regist( 1, [] (IPacket & irPacket ) -> int32 {
        string aID;
        string aPass;
        irPacket >> aID >> aPass;
        NetLib::CSendPacket aPacket( irPacket.Owner(), irPacket.Command() );
        NetLib::CNetworkManager & rNM = NetLib::CNetworkManager::GetInstance();

        DBLib::CDBManager & rDBM = DBLib::CDBManager::GetInstance();
        string aQuery = L"SELECT AID, NICK FROM ACCOUNT WHERE LNAME = " ;
        aQuery << aID << L" AND PWD = SHA1(" << aPass << L")";
        DBLib::result aResult = rDBM.ExecuteStatement( aQuery );
        if( aResult.use_count() < 1 ) {
            NetLib::CSendPacket aPacket( irPacket.Owner(), irPacket.Command() );
            aPacket << false;
            rNM.Send( aPacket );
            return 0;
        }
        aPacket << true;
        uint32 aAID = aResult->GetUInt(0);
        string aNick = aResult->GetString(1);
        aPacket << aAID << aNick;
        rNM.Send( aPacket );
        return 0;
    } );
}