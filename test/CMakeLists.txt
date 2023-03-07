enable_testing()


add_executable(
    common_test
    commonTest.cpp
)
target_include_directories(common_test PUBLIC ${CMAKE_SOURCE_DIR}/common )
target_link_libraries(
    common_test
    GTest::gtest_main
    common
)

include(GoogleTest)
gtest_discover_tests(common_test)