cmake_minimum_required(VERSION 3.17)
project(apue)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Threads)

add_executable(test test.cpp)
add_executable(single multi_thread/single_thread.c)
add_executable(parallel multi_thread/parallel.c)
add_executable(pool multi_thread/using_pool.c multi_thread/pool.h multi_thread/pool.c)

TARGET_LINK_LIBRARIES(parallel  ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(pool  ${CMAKE_THREAD_LIBS_INIT})


