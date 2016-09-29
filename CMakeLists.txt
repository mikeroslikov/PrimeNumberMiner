cmake_minimum_required(VERSION 3.3)
project(Prime_Number_Distribution)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Prime_Number_Distribution ${SOURCE_FILES})