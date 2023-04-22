#pragma once
#include "IDB.h"

namespace JMLib::DBLib 
{
    /**
     * @brief result가 null인 경우의 반환값을 위해 만든다. 
     * result를 받는 쪽에서 항상 null pointer exception을 고려하는 건 피로하다. 
     */
    class CNullResult : public IResult
    {
        public:
        CNullResult() {}
        ~CNullResult() {}

        bool FetchNext() {return false;}

        bool IsNull( const string & irKey ) const { return false; }
        string GetString( const string & irKey ) const { return string(); }
        bool GetBoolean( const string & irKey ) const { return false; }
        int32 GetInt( const string & irKey ) const { return 0; }
        uint32 GetUInt( const string & irKey ) const {return 0;}
        float64 GetFloat64( const string & irKey ) const { return (float64)0 ;}

        bool IsNull( const uint32 iaIndex ) const { return false; }
        string GetString( const uint32 iaIndex ) const { return string(); }
        bool GetBoolean( const uint32 iaIndex ) const { return false; }
        int32 GetInt( const uint32 iaIndex ) const { return 0; }
        uint32 GetUInt( const uint32 iaIndex ) const {return 0;}
        float64 GetFloat64( const uint32 iaIndex ) const { return (float64)0 ;}
        bool IsFirst() const { return false; }
        bool IsLast() const { return false; }
    };
}