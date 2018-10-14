cmake_minimum_required(VERSION 2.6)
project(Intro)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "This is BINARY dir " ${Intro_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${Intro_SOURCE_DIR})

include_directories( 
    "../lib" 
)


add_executable(day_time_client day_time_client.cpp)
add_executable(day_time_server day_time_server.cpp)

if(WIN32)
   target_link_libraries(day_time_client wsock32 ws2_32)
   target_link_libraries(day_time_server wsock32 ws2_32)
endif()