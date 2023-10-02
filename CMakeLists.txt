cmake_minimum_required(VERSION 3.22.0)
project(dijkstra VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(CTest)
enable_testing(True)

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
target_include_directories(dijkstra PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_sources(dijkstra PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dijkstra_by_self_realization_but_boost_graph_container.cpp)


add_test(NAME study_case_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME} ./src/input/1.txt)