#pragma once
#include "IDB.h"

namespace JMLib::DBLib
{
    class CMySQLDB : public IDB 
    {
        private:
        public:
        CMySQLDB();
        ~CMySQLDB();

        bool IsConnect();
        bool Connect( const string & irAddr, const string & irName, const string & irPass );
        result & ExecuteStatement( const string & irString ); 
    }
}