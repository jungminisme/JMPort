cmake_minimum_required(VERSION 3.14.0)
project(JMPort VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
    GoogleTest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories( ${CMAKE_SOURCE_DIR}/common )
add_subdirectory(common)
add_subdirectory(test)

include(CTest)
enable_testing()

add_executable(JMPort main.cpp)
target_link_libraries(JMPort common)  

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
