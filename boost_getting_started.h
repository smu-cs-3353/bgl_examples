//
// Created by mark on 3/29/2021.
//

#ifndef BOOST_GRAPH_BOOST_GETTING_STARTED_H
#define BOOST_GRAPH_BOOST_GETTING_STARTED_H

#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

void example_00() {
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
}


#endif //BOOST_GRAPH_BOOST_GETTING_STARTED_H
