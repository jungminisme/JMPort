#include "MySQLResult.h"
using namespace JMLib::DBLib;

CMySQLResult::CMySQLResult( sql::ResultSet * ipResult ) 
{
    mpResult = ipResult;
}

CMySQLResult::~CMySQLResult()
{
    delete mpResult;
}

/**
 * @brief result set의 결과를 다음 row로 보낸다. 
 * db의 fetch next를 수행
 * @return true 다음 결과를 로드 함. 
 * @return false 더이상 결과가 없음. 현재가 마지막 
 */
bool CMySQLResult::FetchNext()
{
    return mpResult->next();
}

/**
 * @brief 현재 row 에서 data를 가져 온다. 
 * 
 * @param irKey 데이터를 가져갈 key 
 * @param orOutVal 반환 data , 데이터 타입에 상관없이 우선  string으로 준다. 
 * @return int 실패시 에러 반환. exception을 잡을 경우 사용한다. 
 */
int CMySQLResult::GetData( const string & irKey, string & orOutVal )
{
    std::string aKey = irKey.WstrToStr();
    sql::SQLString aRetVal =  mpResult->getString( aKey );
    std::string aRetStr = aRetVal.c_str();
    std::wstring aWRet;
    aWRet.assign( aWRet.begin(), aWRet.end() );
//    orOutVal.Assign( std::w)
    return 0;
}