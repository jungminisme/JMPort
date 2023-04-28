#pragma once
#include "NetCommon.h"

namespace JMLib 
{
    /**
     * @brief callback과의 통신을 위한 데이터 저장 객체 
     * 대부분의 확률로 stream 형태의 객체가 될듯 하다. 
     * netlib쪽에서는 recvPacket을 주로 구현하고, game쪽에서는 sendPacket을 주로 구현한다. 
     * 
     * Packet Header : 아래의 값들은 모든 Packet에 항상 붙어 있어야 한다. 
     * 1. Identifier    : 2Btye     //! 적절한 Packet이 붙었는지 확인 
     * 2. Command       : 2Byte     //! Packet parsing을 위한 번호
     * 3. PacketSize    : 2Byte     //! 패킷의 크기 
     * 
     * Packet별로 fingerprint같은거 뒀다가 읽을때 검증하고 싶지만. 
     * 너무 불편하고 runtime에서 overhead도 심할것으로 예상됨. 
     * 할거면 쓸때도 읽을때도 다 검사해야지.. 여튼 그래서 안한다. 
     */
    class IPacket 
    {
        public:

        protected:
        IPacket() = default;
        ~IPacket() = default;

        public:
        virtual int32 Owner() const = 0;                //! fd를 사용한다. 
        virtual cmd Command() const = 0;                //! Packet 명령어 종류
        virtual uint32 Size() const = 0;                //! Send할 전체 크기
        virtual char * GetBuffer() = 0;                 //! databuffer의 시작점

        //! Packet에 data를 넣을때는 이렇게 넣는 것이 많이 편하다. 
        //! 변수를 개별로 넣는 Append( string ... ) 이런 함수는 나중에 필요하면 만든다. 
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

        //! 변수를 개별로 리턴받는 GetString ... 이런 함수들은 나중에 필요하면 만든다. 
        virtual IPacket & operator >> ( string & orVal ) = 0;
        virtual IPacket & operator >> ( uint8 & orVal ) = 0;
        virtual IPacket & operator >> ( uint16 & orVal ) = 0;
        virtual IPacket & operator >> ( uint32 & orVal ) = 0;
        virtual IPacket & operator >> ( int8 & orVal ) = 0;
        virtual IPacket & operator >> ( int16 & orVal ) = 0;
        virtual IPacket & operator >> ( int32 & orVal ) = 0;
        virtual IPacket & operator >> ( bool & orVal ) = 0;
        virtual IPacket & operator >> ( float32 & orVal ) = 0;
        virtual IPacket & operator >> ( float64 & orVal ) = 0;
    };
}