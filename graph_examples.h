//
// Created by Mark Fontenot on 3/17/2021.
//
// Following along with the Boost Graph Library (BGL) tutorial at:
// https://www.boost.org/doc/libs/1_46_1/libs/graph/doc/quick_tour.html
//

#ifndef BOOST_GRAPH_GRAPH_EXAMPLES_H
#define BOOST_GRAPH_GRAPH_EXAMPLES_H

#include <iostream>
#include <utility>  //std::pair
#include <algorithm>  //std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/config.hpp>
#include <boost/utility.hpp> // for boost::tie
#include <boost/graph/graphviz.hpp>

using namespace boost;

typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
void example_01 ();
void example_02();






#endif //BOOST_GRAPH_GRAPH_EXAMPLES_H
