include_directories(
    "../lib"
)

link_directories(
    "../lib"
)

add_executable(tcpcli01 tcpcli01.cpp)
target_link_libraries(tcpcli01 unp)

add_executable(tcpserv01 tcpserv01.cpp)
target_link_libraries(tcpserv01 unp)

