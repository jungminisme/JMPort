#include "MySQLDB.h"
#include "MySQLResult.h"
#include "ILogger.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace JMLib::DBLib;
CMySQLDB::CMySQLDB()
{
    
}


/**
 * @brief Destroy the CMySQLDB::CMySQLDB object
 * Connection이 남아 있다면 disconnect를 하고 Connection객체를 삭제 한다. 
 */
CMySQLDB::~CMySQLDB()
{
    if( IsConnect() ) 
    {
        mpConn->close();
    }
}

/**
 * @brief Connect상태인지 판단한다. 
 * maConn 객체가 생성되어 있지 않다면, 접속된 적이 없다. 
 * maConn이 있는 경우 생성되었는지 확인한다. 
 * @return true 연결되어 있음. 
 * @return false 연결 안되어 있음. 
 */
bool CMySQLDB::IsConnect()
{
    if( mpConn == NULL )
        return false;
    return mpConn->isValid();
}

/**
 * @brief DB에 접속한다. 
 * 입력받은 DB서버에 접속하고, 사용할 Database 까지 선택한다. 
 * @param irAddr 접속 주소, tcp://127.0.0.1:3306 뭐 이런 형태로 TCP/UDP여부, Port 번호까지 붙여 보낸다. 
 * @param irName DB 사용자 이름
 * @param irPass DB접속 비밀번호
 * @param irDBname 사용할 Database 이름
 * @return true 접속 성공
 * @return false 접속 실패
 */
bool CMySQLDB::Connect( const string & irAddr, const string & irName, 
    const string & irPass, const string & irDBname )
{
    try {
        sql::Driver * aDriver = get_driver_instance();
        if( aDriver == NULL )
            return false;
        mpConn = aDriver->connect( sql::SQLString( irAddr.WstrToStr() ), 
            sql::SQLString( irName.WstrToStr()) , sql::SQLString( irPass.WstrToStr() ) );
        mpConn->setSchema( irDBname.WstrToStr() );
    } 
    catch( sql::SQLException & e ) 
    {
        LOG_ERROR( L"dblist", L"Connection Error : %d", e.getErrorCode() );
        return false;
    }
    return true;
}

/**
 * @brief 입력받은 쿼리를 실행하고 결과를 반환한다. 
 * 
 * @param irString 쿼리 문장
 * @param orRet 결과 set, DBResult의 형태로 반환한다. Output parameter이다. 
 * @return int 에러 여부 
 */
int CMySQLDB::ExecuteStatement( const string & irString, result & orRet )
{
    try {
        if( IsConnect() == false )
            return NError::DNOT_CONNECT;
        sql::Statement * pStatement =  mpConn->createStatement();
        orRet = std::make_shared<CMySQLResult>(
            pStatement->executeQuery( sql::SQLString( irString.WstrToStr() ) )) ;
        delete pStatement;
    }
    catch ( sql::SQLException & e ) 
    {
        LOG_ERROR( L"dblist", L"Connection Error : %d", e.getErrorCode() );
        return e.getErrorCode();
    }
    return 0;
}