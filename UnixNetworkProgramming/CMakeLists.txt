cmake_minimum_required(VERSION 2.6)
project(UNP)

set(CMAKE_CXX_COMPILE "g++")
# set(CMAKE_CXX_FLAGS   "-std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "This is BINARY dir " ${UNP_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${UNP_SOURCE_DIR})

# include_directories( 
#     "../lib" 
# )

# link_directories(
#     "../lib"
# )

add_subdirectory(lib lib)
add_subdirectory(intro intro)
add_subdirectory(tcpcliserv tcpcliserv)