cmake_minimum_required(VERSION 3.16)
project(boost_graph)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.75.0 COMPONENTS graph)

message("Boost Include Directory: " ${Boost_INCLUDE_DIRS})

include_directories(${Boost_INCLUDE_DIRS})
add_executable(boost_graph main.cpp graph_examples.h graph_examples.cpp boost_getting_started.h)
target_link_libraries(boost_graph ${Boost_LIBRARIES})


