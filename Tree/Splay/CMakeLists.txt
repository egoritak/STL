cmake_minimum_required(VERSION 3.14)

project(splay)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES          # All .cpp files in src/
    src/tree.cpp
	include/tree.h
)

add_executable(splay main.cpp)
