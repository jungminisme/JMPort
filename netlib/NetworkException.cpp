#include "NetworkException.h"

using namespace JMLib::NetLib;

CNetworkException::CNetworkException( JMLib::NError::Level iaLevel, const string & irString ) 
    : maLevel( iaLevel ), maMessage( irString )
{ }

JMLib::NError::Level CNetworkException::GetErrorLevel() const 
{
    return maLevel;
}

const JMLib::string & CNetworkException::GetErrorMessage() const
{
    return maMessage;
}
