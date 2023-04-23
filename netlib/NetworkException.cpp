#include "NetworkException.h"

using namespace JMLib::NetLib;

CNetworkException::CNetworkExcetion( JMLib::Level iaLevel, ret_code iaCode, const string & irString ) 
    : maLevel( iaLevel ), maCode( iaCode ), maMessage( irString )
{ }

JMLib::NError::Level CNetworkException::GetErrorLevel() const 
{
    return maLevel;
}

const JMLib::string & CNetworkException::GetErrorMessage() const
{
    return maMessage;
}

ret_code CNetworkException::GetErrorCode() const 
{
    return maCode;
}