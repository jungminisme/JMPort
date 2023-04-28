#pragma once 
#include "IPacket.h"

namespace JMLib::NetLib
{
    /**
     * @brief Packet 기본 구현 
     * 데이터를 보내고 받기 할때의 기본구현
     */
    class CPacket : public IPacket 
    {

        protected:
        int32 maOwner;
        int16 maPos;
        int16 maSize;
        uint16 maCommand;
        char maBuffer[DMAX_PACKET_SIZE];

        public:
        void SetOwner( int32 iaOwner );
        int32 Owner() const;                //! fd를 사용한다. 
        cmd Command() const;                //! Command . Packet parsing을 위한 구분자. 명령어 구분
        uint32 Size() const;                //! Send할 전체 크기
        virtual char * GetBuffer() = 0;                 //! databuffer의 시작점

        IPacket & operator << ( const string & irVal );
        IPacket & operator << ( const uint8 iaVal );
        IPacket & operator << ( const uint16 iaVal );
        IPacket & operator << ( const uint32 iaVal );
        IPacket & operator << ( const int8 iaVal );
        IPacket & operator << ( const int16 iaVal );
        IPacket & operator << ( const int32 iaVal );
        IPacket & operator << ( const bool iaVal );
        IPacket & operator << ( const float32 iaVal );
        IPacket & operator << ( const float64 iaVal );

        IPacket & operator >> ( string & orVal );
        IPacket & operator >> ( uint8 & orVal );
        IPacket & operator >> ( uint16 & orVal );
        IPacket & operator >> ( uint32 & orVal );
        IPacket & operator >> ( int8 & orVal );
        IPacket & operator >> ( int16 & orVal );
        IPacket & operator >> ( int32 & orVal );
        IPacket & operator >> ( bool & orVal );
        IPacket & operator >> ( float32 & orVal );
        IPacket & operator >> ( float64 & orVal );

        protected: 
        CPacket( int32 iaOwner = 0 );
        ~CPacket();
        void AddToBuffer( void * pData, uint16 iaLength );
        void ReadFromBuffer( void * pData, uint16 iaLength );
    };
}