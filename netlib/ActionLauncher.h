#pragma once
#include "IPacket.h"
#include "ICallback.h"

namespace JMLib
{
    /**
     * @brief cmd에 맞는 Callback을 호출 한다. 
     * 
     */
    class CActionLauncher 
    {
        private:
        std::map< cmd, ICallback > maActions;

        public:
        CActionLauncher();
        ~CActionLauncher();
        void Regist(cmd iaCmd, ICallback irCallback );
        void Do( IPacket & irPacket );
    };
}