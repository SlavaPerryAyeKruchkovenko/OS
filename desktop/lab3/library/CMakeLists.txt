cmake_minimum_required(VERSION 3.21)
project(library C)

set(CMAKE_C_STANDARD 23)

add_library(library SHARED library.c)
