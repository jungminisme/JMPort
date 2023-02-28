#include "ILogger.h"
#include "JMString.h"

using namespace JMLib;

void LOG_ERROR( const uint16 iaChannel, wchar_t * ipFormat, ... )
{
    string aOutString;
    va_list aVarList;
    va_start( aVarList, ipFormat);
    aOutString.FormatWithVAList( ipFormat, aVarList );
    va_end( aVarList);
}

void LOG_TRACE( const uint16 iaChannel, wchar_t * ipFormat, ... );
void LOG_INFO( const uint16 iaChannel, wchar_t * ipFormat, ... );
void LOG_DEBUG( const uint16 iaChannel, wchar_t * ipFormat, ... );
void LOG_WARN( const uint16 iaChannel, wchar_t * ipFormat, ... );