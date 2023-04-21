#pragma once
#include "IDB.h"
#include <cppconn/exception.h>
#include <cppconn/resultset.h>

namespace JMLib::DBLib
{
    /**
     * @brief mysql result value의 wrapping class
     * Fectch Next를 해가면서 값을 받아 온다. 
     */
    class CMySQLResult : public IResult
    {
        private:
        sql::ResultSet * mpResult;

        public:
        CMySQLResult(sql::ResultSet * ipResult );
        ~CMySQLResult();

        bool FetchNext();
        string GetString( const string & irKey ) const;
        bool GetBoolean( const string & irKey ) const;
        int32 GetInt( const string & irKey ) const;
        uint32 GetUInt( const string & irKey ) const;
        float64 GetFloat64( const string & irKey ) const;
        string GetString( const uint32 iaIndex ) const;
        bool GetBoolean( const uint32 iaIndex ) const;
        int32 GetInt( const uint32 iaIndex ) const;
        uint32 GetUInt( const uint32 iaIndex ) const;
        float64 GetFloat64( const uint32 iaIndex ) const;

        bool IsFirst() const;
        bool IsLast() const;
        
        private:
        CMySQLResult() {} //! mpResult가 null인 생성자를 막는다. 
    };
}