cmake_minimum_required(VERSION 2.6)
project(Intro)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "This is BINARY dir " ${Intro_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${Intro_SOURCE_DIR})

# include_directories( 
#     "../lib" 
# )

# link_directories(
#     "../lib"
# )

add_subdirectory(
    "./lib"
    "./intro"
    "./tcpcliserv"
)
