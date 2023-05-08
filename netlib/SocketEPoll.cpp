#include "SocketEPoll.h"
#include <unistd.h>

using namespace JMLib::NetLib;

/**
 * @brief Construct a new CSocketEPoll::CSocketEPoll object
 * 생성자. callback을 받지 않는 생성자는 지원하지 않는다. 
 * fd가 열려 있는지 확인 하기 위하여 0으로 초기화 한다. 
 * @param irCallback event 발생시를 위한 callback 
 */
CSocketEPoll::CSocketEPoll( CActionLauncher & irLauncher ) : maFD( 0 ), mrLauncher( irLauncher )
{

}

/**
 * @brief Destroy the CSocketEPoll::CSocketEPoll object
 * 종료시 반드시 socket fd는 닫아준다. 
 */
CSocketEPoll::~CSocketEPoll()
{
    Close();
}

/**
 * @brief fd를 반환한다. server에서 epoll을 하거나 기타 작업을 위한 접근자가 필요하다. 
 * fd는 잘 다뤄야 하므로 여기저기 const를 붙여 둔다. 
 * @return const fd  socket의 file descriptor 
 */
const fd CSocketEPoll::GetFD() const
{
    return maFD;
}

/**
 * @brief 소켓을 닫는다. 
 * fd가 0인 경우는 아예 열리지도 않았던 것으로 간주한다. 
 */
void CSocketEPoll::Close()
{
    if( maFD == 0 )
        return;
    close( maFD );
}