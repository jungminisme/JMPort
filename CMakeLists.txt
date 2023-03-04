cmake_minimum_required(VERSION 3.0.0)
project(JMPort VERSION 0.1.0)


include_directories( ${CMAKE_SOURCE_DIR}/common )
add_subdirectory(common)

include(CTest)
enable_testing()

add_executable(JMPort main.cpp)
target_link_libraries(JMPort common)  

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
