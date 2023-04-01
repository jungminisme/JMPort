enable_testing()
add_executable( JMTest 
    FileTest.cpp
    LoggerTest.cpp
    StringTest.cpp
    DBTest.cpp
)

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
