add_library(dblib STATIC 
    DBManager.cpp 
    MySQLDB.cpp 
    MySQLResult.cpp 
)

target_include_directories(dblib 
PUBLIC
    ${CMAKE_SOURCE_DIR}/dblib
PRIVATE
    /usr/local/include
    /usr/local/include/cppconn
)

target_compile_options( dblib PRIVATE -Wall -Werror -Bdynamic )

target_link_libraries( dblib common mysqlcppconn )
