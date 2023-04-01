#include "MySQLResult.h"
using namespace JMLib::DBLib;

CMySQLResult::CMySQLResult()
{

}

CMySQLResult::~CMySQLResult()
{

}

bool CMySQLResult::FetchNext()
{
    return false;
}

int CMySQLResult::GetData( const string & irKey, string & orOutVal )
{
    return 0;
}