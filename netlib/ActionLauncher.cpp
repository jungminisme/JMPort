#include "ActionLauncher.h"

using namespace JMLib;

CActionLauncher::CActionLauncher() 
{

}

CActionLauncher::~CActionLauncher()
{
    maActions.clear();
}

/**
 * @brief command가 발생하면 수행할 callback을 등록한다. 
 * 
 * @param iaCmd 수행할 command번호
 * @param irCallback 수행할 동작
 */
void CActionLauncher::Regist( cmd iaCmd, ICallback irCallback )
{
    maActions.emplace( iaCmd, irCallback );
}

/**
 * @brief Callback을 수행한다.
 * 
 * @param irPacket callback의 인자값 버퍼
 */
void CActionLauncher::Do( IPacket & irPacket )
{
    auto it = maActions.find( irPacket.Command() );
    if( it != maActions.end() )
        it->second(irPacket);
}