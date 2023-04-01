#pragma once
#include "IDB.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>

namespace JMLib::DBLib
{
    class CMySQLDB : public IDB 
    {
        private:
        sql::Driver * driver;
        public:
        CMySQLDB();
        ~CMySQLDB();

        bool IsConnect();
        bool Connect( const string & irAddr, const string & irName, const string & irPass );
        result & ExecuteStatement( const string & irString ); 
    }
}