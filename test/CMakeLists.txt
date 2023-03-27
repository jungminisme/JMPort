enable_testing()

add_executable(
    JMTest
    StringTest.cpp
    FileTest.cpp
    LoggerTest.cpp
)
target_include_directories(JMTest PUBLIC ${CMAKE_SOURCE_DIR}/common )
target_link_libraries(
    JMTest
    GTest::gtest_main
    common
)

include(GoogleTest)
gtest_discover_tests(JMTest)
