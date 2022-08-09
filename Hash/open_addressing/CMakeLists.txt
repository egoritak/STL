cmake_minimum_required(VERSION 3.1)
project(hash)

set(CMAKE_CXX_STANDARD 14)

include_directories(cpp)
include_directories(headers)

add_executable(hash
        main.cpp)
