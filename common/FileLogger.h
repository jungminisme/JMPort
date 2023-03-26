#pragma once
#include "Logger.h"
#include "JMFile.h"

namespace JMLib 
{
    /**
     * @brief 파일 저장을 위한 로거 
     * 저장할 파일의 이름을 초기화 시에 지정한다. 
     */
    class CFileLogger : public CLogger 
    {
        private:
        CFile maFileOut;
        public:
        CFileLogger();
        ~CFileLogger();

        void LogOut( const string & irString );

        void Initialize( const string & irFileName );
    };

}