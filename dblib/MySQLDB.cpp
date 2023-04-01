#include "MySQLDB.h"
#include "MySQLResult.h"

using namespace JMLib::DBLib;
CMySQLDB::CMySQLDB()
{

}

CMySQLDB::~CMySQLDB()
{

}


bool CMySQLDB::IsConnect()
{
    return false;
}

bool CMySQLDB::Connect( const string & irAddr, const string & irName, const string & irPass )
{
    return false;   
}

int CMySQLDB::ExecuteStatement( const string & irString, result & orRet )
{
    orRet = std::make_shared<CMySQLResult>();
    return 0;
}