#pragma once
#include "IDB.h"
#include <cppconn/connection.h>
#include <cppconn/exception.h>

namespace JMLib::DBLib
{
    /**
     * @brief MySQL DB를 Wrapping 한다. 
     * MySQLConnection만 유지하고, 나머지는 내부 변수로 처리한다. 
     */
    class CMySQLDB : public IDB 
    {
    private:
        sql::Connection * mpConn;
    
    public:
        CMySQLDB();
        ~CMySQLDB();

        bool IsConnect();
        bool Connect( const string & irAddr, const string & irName, 
            const string & irPass, const string & irDBName );
        result ExecuteStatement( const string & irString ); 
        bool Close();
    };
}