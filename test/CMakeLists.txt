enable_testing()
file( GLOB SOURCES "*.cpp")

add_executable( JMTest ${SOURCES} )

target_include_directories( 
    JMTest PUBLIC 
    ${CMAKE_SOURCE_DIR}/common 
    ${CMAKE_SOURCE_DIR}/dblib 
)

target_link_libraries(
    JMTest
    GTest::gtest_main
    common
    dblib
)

include(GoogleTest)
gtest_discover_tests(JMTest)
