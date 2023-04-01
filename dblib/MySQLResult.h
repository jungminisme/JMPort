#pragma once
#include "IDB.h"
#include <cppconn/exception.h>
#include <cppconn/resultset.h>

namespace JMLib::DBLib
{
    class CMySQLResult : public IResult
    {
        CMySQLResult();
        ~CMySQLResult();

        bool FetchNext();
        int GetData( const string & irkey, string & orOutVal );
    }
}