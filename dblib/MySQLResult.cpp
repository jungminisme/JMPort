#include "MySQLResult.h"
using namespace JMLib::DBLib;

/**
 * @brief Construct a new CMySQLResult::CMySQLResult object
 * 기본 생성자. 반드시 result는 있어야 한다. 
 * @param ipResult MySQL의 result set
 */
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
 * @brief Key에 해당하는 컬럼이 존재하는지 반환한다. 
 * 
 * @param irKey 찾으려는 컬럼의 키
 * @return true 컬럼이 있는 경우
 * @return false 컬럼이 존재하지 않는경우
 */
bool CMySQLResult::IsNull( const string & irKey ) const
{
    return mpResult->isNull( irKey.WstrToStr() );
}

/**
 * @brief 키로 컬럼을 찾아 문자열을 반환
 * 
 * @param irKey 찾으려는 컬럼의 label 
 * @return JMLib::string 문자열 결과값
 */
JMLib::string CMySQLResult::GetString( const string & irKey ) const
{
    std::string aKey = irKey.WstrToStr();
    sql::SQLString aRetVal =  mpResult->getString( aKey );
    std::string aRetStr = aRetVal.c_str();
    return JMLib::string( aRetStr );
}

/**
 * @brief 키로 컬럼을 찾아 불 값 반환
 * 
 * @param irKey 찾으려는 컬럼의 label 
 * @return bool 결과값
 */
bool CMySQLResult::GetBoolean( const string & irKey ) const
{
    return mpResult->getBoolean( irKey.WstrToStr() );
}

/**
 * @brief 키로 컬럼을 찾아 정수형 반환 (int32)
 * 
 * @param irKey 찾으려는 컬럼의 label 
 * @return JMLib::int32 결과값
 */
JMLib::int32 CMySQLResult::GetInt( const string & irKey ) const
{
    return mpResult->getInt( irKey.WstrToStr() );
}

/**
 * @brief 키로 컬럼을 찾아 정수형 반환(uint32)
 * 
 * @param irKey 찾으려는 컬럼의 label 
 * @return JMLib::uint32 결과값
 */
JMLib::uint32 CMySQLResult::GetUInt( const string & irKey ) const
{
    return mpResult->getUInt( irKey.WstrToStr() );
}

/**
 * @brief 키로 컬럼을 찾아 부동소수점 숫자 반환
 * 
 * @param irKey 찾으려는 컬럼의 label 
 * @return JMLib::float64 결과값
 */
JMLib::float64 CMySQLResult::GetFloat64( const string & irKey ) const
{
    return mpResult->getDouble( irKey.WstrToStr() );
}

/**
 * @brief 인덱스에 해당하는 컬럼이 존재하는지 반환
 * 
 * @param iaIndex 찾으려는 인덱스
 * @return true 컬럼이 존재하는 경우
 * @return false 컬럼이 존재하지 않는 경우 
 */
bool CMySQLResult::IsNull( const JMLib::uint32 iaIndex ) const 
{
    return mpResult->isNull( iaIndex );
}

/**
 * @brief 인덱스로 컬럼을 찾아 문자열 반환
 * 
 * @param iaIndex 찾으려는 컬럼의 index 
 * @return JMLib::string 결과 문자열
 */
JMLib::string CMySQLResult::GetString( const JMLib::uint32 iaIndex ) const
{
    sql::SQLString aRetVal =  mpResult->getString( iaIndex );
    return JMLib::string( std::string( aRetVal.c_str() ) );
}

/**
 * @brief 인덱스로 컬럼을 찾아 불 값 반환
 * 
 * @param iaIndex 찾으려는 컬럼의 index
 * @return bool 결과값
 */
bool CMySQLResult::GetBoolean( const JMLib::uint32 iaIndex ) const
{
    return mpResult->getBoolean( iaIndex );
}

/**
 * @brief 인덱스로 컬럼을 찾아 정수형 값 반환(int32)
 * 
 * @param iaIndex 찾으려는 컬럼의 index
 * @return JMLib::int32 결과값
 */
JMLib::int32 CMySQLResult::GetInt( const JMLib::uint32 iaIndex ) const
{
    return mpResult->getInt( iaIndex );
}

/**
 * @brief 인덱스로 컬럼을 찾아 정수형 값 반환( uint32 )
 * 
 * @param iaIndex 찾으려는 컬럼의 index
 * @return JMLib::uint32 결과값
 */
JMLib::uint32 CMySQLResult::GetUInt( const JMLib::uint32 iaIndex ) const
{
    return mpResult->getUInt( iaIndex );
}

/**
 * @brief 인덱스로 컬럼을 찾아 부동소수점 값 반환
 * 
 * @param iaIndex 찾으려는 컬럼의 index
 * @return JMLib::float64 결과값
 */
JMLib::float64 CMySQLResult::GetFloat64( const JMLib::uint32 iaIndex ) const
{
    return mpResult->getDouble( iaIndex );
}

/**
 * @brief 첫번째 로우인지 판단
 * 
 * @return true 첫번째 로우
 * @return false 첫번째 로우 아님 
 */
bool CMySQLResult::IsFirst() const
{
    return mpResult->isFirst();
}

/**
 * @brief 마지막 로우인지 판단
 * 
 * @return true 마지막 로우
 * @return false 마지막 로우 아님
 */
bool CMySQLResult::IsLast() const
{
    return mpResult->isLast();
}
