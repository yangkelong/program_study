

project(MY_LIB)
cmake_minimum_required(VERSION 3.5)
message (">>> CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message (">>> CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message (">>> CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message (">>> CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 11)


add_library(mylib
  mylib.h
  mylib.cpp
  )

