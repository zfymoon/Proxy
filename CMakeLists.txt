cmake_minimum_required(VERSION 3.16)
project(Zhuque)

set(CMAKE_CXX_STANDARD 20)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Boost 1.65.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Zhuque main.cpp Config.h base/Protocol.h server/TCPServer.h base/Log.h server/SessionHandler.h client/TCPClient.h client/ClientProtocol.h server/ServerProtocol.h)

target_link_libraries(Zhuque ${Boost_LIBRARIES}  Threads::Threads)


