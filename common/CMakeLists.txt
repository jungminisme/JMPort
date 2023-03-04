add_library(common STATIC ConsoleLogger.cpp FileLogger.cpp ILogger.cpp JMFile.cpp 
JMString.cpp Logger.cpp LogManager.cpp )
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR}/common)
target_compile_options(common PRIVATE -Wall -Werror )