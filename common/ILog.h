#pragma once
#include "JMDataType.h"

using namespace JMLib;

namespace NLog
{
    namespace NLevel 
    {
        /// @brief 로그의 분류
        const static uint8 DTRACE = 1;   
        const static uint8 DDEBUG = 2;
        const static uint8 DINFO = 3;
        const static uint8 DWARN = 4;   
        const static uint8 DERROR = 5;
        const static uint8 DFATAL = 6;

        /// @brief Log Filtering 시에만 사용하는 레벨
        const static uint8 DNONNE = 7;      //! 로그를 남기지 않음 
        const static uint8 DALL = 1;        //! 모든 로그를 남김
    }

    namespace NType
    {
        const static uint8 DCONSOLE = 1;
        const static uint8 DFILE = 2;
        const static uint8 DNETWORK = 3;
    }
}

class ILogger
{
    public:
    ILogger() {}
    virtual ~ILogger() {}

};