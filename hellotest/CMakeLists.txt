cmake_minimum_required(VERSION 3.6)
project(hellotest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(hellotest ${SOURCE_FILES})