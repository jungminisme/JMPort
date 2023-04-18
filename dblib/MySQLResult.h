#pragma once
#include "IDB.h"
#include <cppconn/exception.h>
#include <cppconn/resultset.h>

namespace JMLib::DBLib
{
    class CMySQLResult : public IResult
    {
        private:
        sql::ResultSet * mpResult;

        public:
        CMySQLResult(sql::ResultSet * ipResult );
        ~CMySQLResult();

        bool FetchNext();
        int GetData( const string & irkey, string & orOutVal );
    };
}