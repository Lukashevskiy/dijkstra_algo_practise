cmake_minimum_required(VERSION 3.22.0)
project(dijkstra VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(
    Boost REQUIRED COMPONENTS 
        graph 
        thread 
        system
)

add_executable(dijkstra)

target_link_directories(
    dijkstra PRIVATE 
        Boost::graph
        Boost::system
        Boost::thread
)

target_sources(dijkstra PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dijkstra_by_boost.cpp)