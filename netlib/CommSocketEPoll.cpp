#include "CommSocketEPoll.h"

using namesapce JMLib::NetLib;

CCommSocketEPoll::CCommSocketEPoll( ICallback & irCallback ) : CSocketEPoll( irCallback )
{
}

CCommSocketEPoll::~CCommSocketEPoll()
{
}

int32 CCommSocketEPoll::OnEvent(const uint32 iaEvent) const
{
    return int32();
}

void CCommSocketEPoll::Init(fd iaFD)
{
    maFD = iaFD;
    int32 aFlag = fcntl( maFD, F_GETFL );
    aFlag |= O_NONBLOCK;
    int aRet = fcntl( maFD, F_SETFL, aFlag );
    if( aRet < 0 )
        throw CNetworkException( NError::NLevel::DERROR, L"fcntl() fuction Fail" );
}
