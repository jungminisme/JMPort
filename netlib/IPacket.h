#pragma once
#include "JMString.h"

namespace JMLib 
{
    class IPacket 
    {
        protected:
        IPacket() = default;
        ~IPacket() = default;

        public:
        virtual uint32 ID() = 0;
        virtual uint32 Size() = 0;

        virtual IPacket & operator << ( const string & irVal ) = 0;
        virtual IPacket & operator << ( const uint8 iaVal ) = 0;
        virtual IPacket & operator << ( const uint16 iaVal ) = 0;
        virtual IPacket & operator << ( const uint32 iaVal ) = 0;
        virtual IPacket & operator << ( const int8 iaVal ) = 0;
        virtual IPacket & operator << ( const int16 iaVal ) = 0;
        virtual IPacket & operator << ( const int32 iaVal ) = 0;
        virtual IPacket & operator << ( const bool iaVal ) = 0;
        virtual IPacket & operator << ( const float32 iaVal ) = 0;
        virtual IPacket & operator << ( const float64 iaVal ) = 0;

        virtual string GetString() = 0;
        virtual uint8 GetUInt8() = 0;
        virtual uint16 GetUInt16() = 0;
        virtual uint32 GetUInt32() = 0;
        virtual int8 Getnt8() = 0;
        virtual int16 GetInt16() = 0;
        virtual int32 GetInt32() = 0;
        virtual bool GetBoolean() = 0;
        virtual float32 GetFloat32() = 0;
        virtual float64 GetFloat64() = 0;
    };
}