#pragma once

namespace JMLib::DBLib
{
    class CMySQLResult : public IResult
    {
        CMySQLResult();
        ~CMySQLResult();

        bool FetchNext();
        int GetData( const string & irkey, string & orOutVal );
    }
}