#include "DBManager.h"

using namespace JMLib::DBLib;

CDBManager & CDBManager::GetInstance()
{
    static CDBManager saInstance;
    return saInstance;
}

bool CDBManager::Connect(const string & irAddr, const string & irName, const string & irPass)
{
    if( maDB )
        return true;
    return false;
}

int  CDBManager::ExecuteStatement(const string & irString, result & orResult)
{
    return maDB->ExecuteStatement( irString, orResult );
}
