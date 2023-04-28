#pragma once
#include "IPacket.h"

namespace JMLib::NetLib
{
    /**
     * @brief System 내부 사용을 위한 Packet 
     * Owner와 Command만을 사용한다. 
     * DataSetting을 위한 모든 함수는 Exception을 던진다. 
     */
    class CSysPacket : public IPacket 
    {
        private:
        cmd maCommand;
        int32 maOwner;
        
        public:
        CSysPacket( int32 iaOwner = 0, cmd iaCmd = 0 );
        ~CSysPacket();

        void SetOwner( int32 iaOwner );
        int32 Owner() const;                //! fd를 사용한다. 
        cmd Command() const;                //! Command . Packet parsing을 위한 구분자. 명령어 구분
        uint32 Size() const;                //! Send할 전체 크기 // HeaderSize
        char * GetBuffer();                 //! databuffer의 시작점 // 사용하지 않음

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
    };
}