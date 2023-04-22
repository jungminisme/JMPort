#pragma once
#include "JMString.h"
#include <memory>

namespace JMLib::DBLib
{
    /// @brief 
    namespace NError
    {
        const static int16 DNOT_CONNECT  = -1;
    } // namespace NError
    
    /**
     * @brief DB result set에 대한 Interface class
     * 다수의 결과를 return 해야할 필요가 있기에 FetchNext를 만든다. 
     * result의 실제 구현을 외부와 격리하기 위해 만든다. 
     */
    class IResult 
    {
        public:
        IResult() = default;
        ~IResult() = default;

        virtual bool FetchNext() = 0;

        virtual bool IsNull( const string & irKey ) const = 0;
        virtual string GetString( const string & irKey ) const = 0;
        virtual bool GetBoolean( const string & irKey ) const = 0;
        virtual int32 GetInt( const string & irKey ) const = 0;
        virtual uint32 GetUInt( const string & irKey ) const = 0;
        virtual float64 GetFloat64( const string & irKey ) const = 0;

        virtual bool IsNull( const uint32 iaIndex ) const = 0;
        virtual string GetString( const uint32 iaIndex ) const = 0;
        virtual bool GetBoolean( const uint32 iaIndex ) const = 0;
        virtual int32 GetInt( const uint32 iaIndex ) const = 0;
        virtual uint32 GetUInt( const uint32 iaIndex ) const = 0;
        virtual float64 GetFloat64( const uint32 iaIndex ) const = 0;

        virtual bool IsFirst() const = 0;
        virtual bool IsLast() const = 0;
    };
    typedef std::shared_ptr< IResult > result;

    /**
     * @brief DataBase 객체 의 Interface 
     * connection 및 기타 DB의 개념적 최상위 클래스. 
     * DB의 실제 구현을 외부와 격리하기 위해 만든다. 
     */
    class IDB 
    {
        public:
        IDB() = default;
        ~IDB() = default;

        virtual bool IsConnect() = 0;
        virtual bool Connect( const string & irAddr, const string & irName, 
            const string & irPass, const string & irDBName ) = 0;
        virtual result ExecuteStatement( const string & irString  ) = 0; 
        virtual bool Close() = 0;
    };

    typedef std::shared_ptr< IDB > db;
}