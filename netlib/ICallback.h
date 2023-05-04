#pragma once
#include "IPacket.h"
namespace JMLib
{
    /**
     * @brief Callback을 위한 interface 
     * 선언은 이곳에 되어 있지만 실제 구현은 Contents 쪽에서 한다. 
     */
   typedef std::function< int32 ( const IPacket & ) > ICallback;
}