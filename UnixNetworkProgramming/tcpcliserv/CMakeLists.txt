include_directories(
    ${UNP_SOURCE_DIR}/lib
)

link_directories(
    ${UNP_BINARY_DIR}/lib
)

add_executable(tcpcli01 tcpcli01.cpp)
target_link_libraries(tcpcli01 unp)

add_executable(tcpserv01 tcpserv01.cpp)
target_link_libraries(tcpserv01 unp)

add_executable(tcpcli04 tcpcli04.cpp)
target_link_libraries(tcpcli04 unp)

add_executable(tcpserv04 tcpserv04.cpp sigchldwaitpid.cpp)
target_link_libraries(tcpserv04 unp)

