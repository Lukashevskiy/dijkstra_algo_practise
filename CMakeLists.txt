cmake_minimum_required(VERSION 3.20)
project(dijkstra VERSION 0.1.0 LANGUAGES CXX)

add_compile_options(--std=c++23 -Wall -v)
add_executable(dijkstra main.cpp)