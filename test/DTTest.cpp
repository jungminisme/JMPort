#include "../common/JMDataType.h"

using namespace JMLib;

int main()
{

    printf( "Data size of int8 is %lu\n", sizeof( int8 ) );
    printf( "Data size of uint8 is %lu\n", sizeof( uint8 ));

    printf( "Data size of int16 is %lu\n", sizeof( int16 ) );
    printf( "Data size of uint16 is %lu\n", sizeof( uint16 ));
    printf( "Data size of int32 is %lu\n", sizeof( int32 ) );
    printf( "Data size of uint32 is %lu\n", sizeof( uint32 ));
    printf( "Data size of float32 is %lu\n", sizeof( float32 ) );
    printf( "Data size of float64 is %lu\n", sizeof( float64 ));
    return 0;
}