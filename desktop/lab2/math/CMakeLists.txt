cmake_minimum_required(VERSION 3.21)
project(math C)

set(CMAKE_C_STANDARD 23)

add_library(math SHARED library.c)
