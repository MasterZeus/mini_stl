cmake_minimum_required(VERSION 3.10)
project(mini_stl)

set(CMAKE_CXX_STANDARD 11)

add_executable(mini_stl main.cpp Container/Vector.cpp Container/Vector.h Allocator/alloc.cpp Allocator/alloc.h Allocator/Allocator.h)