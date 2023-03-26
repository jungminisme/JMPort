enable_testing()

add_executable(
    LoggerTest
    LoggerTest.cpp
)
target_include_directories(LoggerTest PUBLIC ${CMAKE_SOURCE_DIR}/common )
target_link_libraries(
    LoggerTest
    GTest::gtest_main
    common
)

add_executable(
    FileTest
    FileTest.cpp
)
target_include_directories(FileTest PUBLIC ${CMAKE_SOURCE_DIR}/common )
target_link_libraries(
    FileTest
    GTest::gtest_main
    common
)

add_executable(
    StringTest
    StringTest.cpp
)
target_include_directories(StringTest PUBLIC ${CMAKE_SOURCE_DIR}/common )
target_link_libraries(
    StringTest
    GTest::gtest_main
    common
)

include(GoogleTest)
gtest_discover_tests(FileTest)
gtest_discover_tests(StringTest)
gtest_discover_tests(LoggerTest)