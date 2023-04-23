#pragma once
#include "IPacket.h"
namespace JMLib
{
    class ICallback
    {
        protected:
        ICallback() = default;
        ~ICallback() = default;

        virtual int Post( const IPacket & irPacket ) const = 0;
    };
}