#include "NetworkException.h"

using namespace JMLib::NetLib;

/**
 * @brief Construct a new CNetworkException::CNetworkException object
 * 예외를 발생시키는 것조차 몇줄씩인게 마음에 안들어 생성자에서 인자를 다 받는다. 
 * @param iaLevel 에러 레벨
 * @param irString 메시지 
 */
CNetworkException::CNetworkException( JMLib::NError::Level iaLevel, const string & irString ) 
    : maLevel( iaLevel ), maMessage( irString )
{ }

/**
 * @brief 얼마나 치명적인 에러인지의 등급
 * 
 * @return JMLib::NError::Level 등급
 */
JMLib::NError::Level CNetworkException::GetErrorLevel() const 
{
    return maLevel;
}

/**
 * @brief 실제 에러의 내용을 설명해 준다. 
 * 
 * @return const JMLib::string& 메시지
 */
const JMLib::string & CNetworkException::GetErrorMessage() const
{
    return maMessage;
}

/**
 * @brief std::exception을 위한 구현
 * std::exception에서는 char* 만을 사용하기에 해당 구현을 넣어 놓는다. 
 * @return const char* 에러 메시지 
 */
const char * CNetworkException::what() const noexcept 
{
    return maMessage.WstrToStr().c_str();
}