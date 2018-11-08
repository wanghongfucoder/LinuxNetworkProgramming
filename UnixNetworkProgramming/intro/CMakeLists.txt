# cmake_minimum_required(VERSION 2.6)
# project(Intro)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# message(STATUS "This is BINARY dir " ${Intro_BINARY_DIR})
# message(STATUS "This is SOURCE dir " ${Intro_SOURCE_DIR})

include_directories( 
    ${UNP_SOURCE_DIR}/lib
)

link_directories(
    ${UNP_BINARY_DIR}/lib
)

add_executable(day_time_client day_time_client.cpp)
target_link_libraries(day_time_client unp)

add_executable(day_time_server day_time_server.cpp)
target_link_libraries(day_time_server unp)

add_executable(day_time_server1 day_time_server1.cpp)
target_link_libraries(day_time_server1 unp)

add_executable(byte_order byte_order.cpp)
target_link_libraries(byte_order unp)


