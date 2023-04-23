#include "DBManager.h"
#include "MySQLDB.h"
#include "LogManager.h"

using namespace JMLib::DBLib;

CDBManager::CDBManager() 
{
    maDB = std::make_shared<CMySQLDB>();
    //! 로거를 설정한다. 
    CLogManager & aLM = CLogManager::GetInstance();
    aLM.AddLogger( L"dblib", JMLib::NLog::NType::DCONSOLE, JMLib::NLog::NLevel::DALL );
}

CDBManager & CDBManager::GetInstance()
{
    static CDBManager saInstance;
    return saInstance;
}

/**
 * @brief DB에 접속 한다. 
 * 
 * @param irAddr 서버의 hostname
 * @param irName db user name
 * @param irPass db user의 비밀번호
 * @return true 접속 성공
 * @return false 
 */
bool CDBManager::Connect(const string & irAddr, const string & irName, 
    const string & irPass, const string & irDBName )
{
    return maDB->Connect(irAddr, irName, irPass, irDBName );
}

result CDBManager::ExecuteStatement(const string & irString )
{
    return maDB->ExecuteStatement( irString );
}

bool CDBManager::Close() 
{
    return maDB->Close();
}