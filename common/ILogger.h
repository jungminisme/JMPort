#pragma once
#include "JMDataType.h"
#include "JMString.h"

namespace JMLib
{
    namespace NLog
    {
        typedef uint8 LevelType;
        typedef uint8 LogType;
        typedef string LogChannel;

        namespace NLevel 
        {
            /// @brief 로그의 등급
            const static LevelType DTRACE = 1;   
            const static LevelType DDEBUG = 2;
            const static LevelType DINFO = 3;
            const static LevelType DWARN = 4;   
            const static LevelType DERROR = 5;
            const static LevelType DFATAL = 6;

            /// @brief Log Filtering 시에만 사용하는 레벨
            const static LevelType DNONNE = 7;      //! 로그를 남기지 않음 
            const static LevelType DALL = 0;        //! 모든 로그를 남김
        }

        namespace NType
        {
            const static LogType DNONE = 0;         //! 아무것도 하지 않는 로거
            const static LogType DCONSOLE = 1;      //! 화면 출력 로거
            const static LogType DFILE = 2;         //! 파일 출력 로거
            const static LogType DXML = 3;          //! XML 출력 로거       // 추후 구현
            const static LogType DNETWORK = 4;      //! 네트워크 출력 로거  // 추후 구현
        }
    }

    class ILogger
    {
        public:
        ILogger() {}
        virtual ~ILogger() {}

        virtual void Initialize( const string & irString ) = 0;
        virtual void Log( const string & irString ) = 0;
        virtual void LogWithLevel( const NLog::LevelType iaType, const string & irString ) = 0;
        virtual void LogWithAllArg( const string & irSrcFile, const uint32 iaLine, 
            const NLog::LevelType iaLevel, const string & irLogString ) = 0;
            
    };

    typedef std::shared_ptr<ILogger> slogger;

}

//* 기본 채널에 로그를 남길때 
void LOG_ERROR( wchar_t * ipFormat, ... );
void LOG_TRACE( wchar_t * ipFormat, ... );
void LOG_INFO( wchar_t * ipFormat, ... );
void LOG_DEBUG( wchar_t * ipFormat, ... );
void LOG_WARN(  wchar_t * ipFormat, ... );

//* 원하는 채널에 로그를 남길때 
void LOG_ERROR( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFormat, ... );
void LOG_TRACE( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFormat, ... );
void LOG_INFO( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFormat, ... );
void LOG_DEBUG( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFormat, ... );
void LOG_WARN( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFormat, ... );

//* 원하는 채널에 파일 이름과 라인 번호를 가지고 로그를 남길때 
void LOG_ERROR( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFileName, JMLib::int32 iaLine,  wchar_t * ipFormat, ... );
void LOG_TRACE( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFileName, JMLib::int32 iaLine, wchar_t * ipFormat, ... );
void LOG_INFO( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFileName, JMLib::int32 iaLine, wchar_t * ipFormat, ... );
void LOG_DEBUG( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFileName, JMLib::int32 iaLine, wchar_t * ipFormat, ... );
void LOG_WARN( const JMLib::NLog::LogChannel & irChannel, wchar_t * ipFileName, JMLib::int32 iaLine, wchar_t * ipFormat, ... );
void LOG_FATAL(const JMLib::NLog::LogChannel &irChannel, wchar_t *ipFileName, JMLib::int32 iaLine, wchar_t *ipFormat, ...);
