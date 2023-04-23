#pragma once
#include "JMString.h"
#include "IDB.h"

namespace JMLib::DBLib
{
    /**
     * @brief DB를위한 싱글톤이자 facade로 둔다. 
     * 일단 이곳에서 인터페이스를 하고 구현은 뒤로 숨긴다. 
     * 특정 DB를 위한 전용코드가 프로젝트 전체에 영향을 미치는 건 좀 별로다. 
     */
    class CDBManager
    {
        private:
        db maDB;

        public:
        static CDBManager & GetInstance();

        bool Connect( const string & irAddr, const string & irName, 
            const string & irPass, const string & irDBName );
        result ExecuteStatement( const string & irString );
        bool Close();

        private:
        CDBManager();
        ~CDBManager() = default;
    };
}