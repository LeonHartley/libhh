cmake_minimum_required(VERSION 3.6)
project(libhh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES libhh.h libhh.c)
add_executable(libhh ${SOURCE_FILES})