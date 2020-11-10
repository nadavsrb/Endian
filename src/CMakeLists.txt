cmake_minimum_required(VERSION 3.0.0)
project(Endian)


include_directories(${CMAKE_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR})


add_executable(endian.out main.c ex1.c)