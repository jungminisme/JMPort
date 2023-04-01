file( GLOB SOURCES "*.cpp")
add_library( common STATIC ${SOURCES} )
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR}/common)
target_compile_options(common PRIVATE -Wall -Werror )