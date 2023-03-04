#include "LogManager.h"
#include "NoneLogger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include <memory>

/**
 * @brief 싱글톤 패턴을 위한 함수 
 * 전체 시스템에서 로그 관련 관리자는 한개만 있으면 된다. 
 * @return CLogManager& 전역 로그 관리자 객체
 */
CLogManager * CLogManager::GetInstance()
{
    return & maInstance;
}

/**
 * @brief 채널에 해당 타입의 로거를 등록한다. 
 * 같은 이름의 채널이 이미 등록되어 있는 경우 등록하지 않고 실패를 반환한다. 
 * Logger factory를 따로 만들지 말고 여기서 생성까지 하자. 
 * 로거는 복잡하지도 않으니. 
 * TODO : 추후 이부분에 Excpetion을 추가한다. 
 * @param irChannel 등록을 원하는 채널 
 * @param iaType 로거의 종류
 * @return true 로거 등록에 성공
 * @return false  같은 이름이 있거나, 로거 타입을 정못적은 경우 실패 
 */
bool CLogManager::SetLogger( const NLog::LogChannel & irChannel, NLog::LogType iaType )
{
    lockguard aLG(maLock );
    
    slogger aLogger;
    switch( iaType )
    {
        case NLog::NType::DNONE:
            aLogger = std::make_shared<CNoneLogger>();
            break;
        case NLog::NType::DCONSOLE:
            aLogger = std::make_shared<CConsoleLogger>();
            break;
        case NLog::NType::DFILE:
        aLogger = std::make_shared<CFileLogger>();
        {
            string aTempString( irChannel );
            aTempString << L".log";
            aLogger->Initialize(aTempString);
        }
            break;
        default:
            return false;
    }

    string aChannel ;
    aChannel = irChannel;
    std::pair<logs::iterator, bool > aRet;
    aRet = maLogs.insert( logs::value_type(aChannel, aLogger ));
    return aRet.second;
}

/**
 * @brief 록거를 제거 한다. 
 * 중간에 쓸일이 있을지 모르지만. 로거 생성이 있으니 삭제도 만들어 본다. 
 * @param iaChannel 등록된 채널
 */
void CLogManager::RemoveLogger( const NLog::LogChannel & irChannel )
{
    lockguard aLG( maLock );
    logs::iterator aIt = maLogs.find( irChannel );
    if( aIt == maLogs.end() )
        return;
    maLogs.erase(aIt);
}

/**
 * @brief 로그를 남긴다. 
 * 별도의 로그레벨을 지정하지 않고 로그를 남기는 경우 이다. 
 * 이때는 임의로 DEBUG Level 로 설정한다. 
 * @param iaChannel 출력될 로그의 채널
 * @param irString  출력할 로그
 */
void CLogManager::Log( const NLog::LogChannel & irChannel, const string & irString )
{
    LogWithLevel( irChannel, NLog::NLevel::DDEBUG, irString );
}

/**
 * @brief Level 로 로그를 남긴다. 
 * 실제로 로그채널에서 로거를 찾아서 로그를 남기는 부분
 * @param iaChannel 로그를 출력할 채널
 * @param iaLevel 로그레벨
 * @param irString 출력될 로그
 */
void CLogManager::LogWithLevel( const NLog::LogChannel & irChannel, NLog::LevelType iaLevel, const string & irString )
{
    lockguard aLG( maLock );
    logs::iterator it = maLogs.find(irChannel );
    if( it == maLogs.end() )
        return;
    slogger aLog = it->second;
    aLog->LogWithLevel( iaLevel, irString );
}

/**
 * @brief 소스파일이름, 라인등 모든 정보를 포함한 로그를 날린다. 
 * 
 * @param iaChannel 출력할 로그체널
 * @param irSrcFile 로그가 발생한 소스파일
 * @param iaLine  로그 발생 소스 라인
 * @param iaLevel 로그 등급
 * @param irLogString 로그 내용
 */
void CLogManager::LogWithAllArg( const NLog::LogChannel & irChannel, string & irSrcFile, const uint32 iaLine, 
        const NLog::LevelType iaLevel, const string & irLogString )
{
    lockguard aLG( maLock );
    logs::iterator it = maLogs.find(irChannel );
    if( it == maLogs.end() )
        return;
    slogger aLog = it->second;
    aLog->LogWithAllArg(irSrcFile, iaLine, iaLevel, irLogString );
}

