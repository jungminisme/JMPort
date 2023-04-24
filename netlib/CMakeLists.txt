add_library( netlib STATIC 
    NetworkManager.cpp
    ServerEPoll.cpp
    NetworkException.cpp
    SocketEPoll.cpp 
    ListenSocketEPoll.cpp 
    CommSocketEPoll.cpp 
)

target_include_directories(
    netlib
    PUBLIC
    ${CMAKE_SORUCE_DIR}/netlib
)

target_compile_options( netlib PRIVATE -Wall -Werror -Bdynamic )
target_link_libraries( netlib common )