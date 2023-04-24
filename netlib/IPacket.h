#pragma once
#include "JMString.h"

namespace JMLib 
{
    /**
     * @brief callback과의 통신을 위한 데이터 저장 객체 
     * 대부분의 확률로 stream 형태의 객체가 될듯 하다. 
     * netlib쪽에서는 recvPacket을 주로 구현하고, game쪽에서는 sendPacket을 주로 구현한다. 
     */
    class IPacket 
    {
        protected:
        IPacket() = default;
        ~IPacket() = default;

        public:
        virtual int32 ID() const = 0;                   //! fd를 사용한다. 
        virtual uint32 Size() const = 0;                //! Send할 전체 크기
        virtual const char * GetBuffer() const = 0;     //! databuffer의 시작점

        //! Packet에 data를 넣을때는 이렇게 넣는 것이 많이 편하다. 
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

        //! Packet으로 부터 Data를 얻을때는. .. 중간에 data byte가 어긋나는 경우 체크를 하자. 
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