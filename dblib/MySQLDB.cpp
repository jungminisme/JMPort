#include "MySQLDB.h"

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

result & CMySQLDB::ExecuteStatement( const string & irString )
{
}