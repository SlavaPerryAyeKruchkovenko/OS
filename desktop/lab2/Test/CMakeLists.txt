cmake_minimum_required(VERSION 3.21)
project(Test)

set(CMAKE_CXX_STANDARD 23)

link_directories(lib)

add_executable(Test main.cpp)

target_link_libraries(Test libmath.dll)
