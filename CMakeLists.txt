cmake_minimum_required(VERSION 3.16)
project(boost_graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(boost_graph main.cpp graph_examples.h graph_examples.cpp boost_getting_started.h)