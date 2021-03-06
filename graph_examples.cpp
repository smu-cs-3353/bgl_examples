//
// Created by mark on 3/17/2021.
//

#include "graph_examples.h"



void example_01 () {
//    enum nodes {A, B, C, D, E};
//    const int num_nodes = 5;
//
//    typedef std::pair<int, int> Edge;
//
//    Edge edge_array[] = {
//            Edge(nodes.A, nodes.B),
//            Edge(nodes.A, nodes.D),
//            Edge(nodes.C, nodes.A),
//            Edge(nodes.D, nodes.C),
//            Edge(nodes.C, nodes.E),
//            Edge(nodes.B, nodes.D),
//            Edge(nodes.D, nodes.E)
//    };


    // create a typedef for the Graph type
    typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

    // Make convenient labels for the vertices
    enum { A, B, C, D, E, N };
    const int num_vertices = N;
    const char* name = "ABCDE";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
            { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
              Edge(C,E), Edge(B,D), Edge(D,E) };

    const int num_edges = 7;

    Graph g(num_vertices);
    for(int i = 0; i < num_edges; i++)
        add_edge(edge_array[i].first, edge_array[i].second, g);

    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    // get the property map for vertex indices
    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);

    std::cout << "vertices(g) = ";
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
        Vertex v = *vp.first;
        std::cout << index[v] <<  " ";
    }
    std::cout << std::endl;

    std::cout << "edges(g) = ";
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        std::cout << "(" << index[source(*ei, g)]
                  << "," << index[target(*ei, g)] << ") ";
    std::cout << std::endl;
}

//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

// from https://www.boost.org/doc/libs/1_75_0/libs/graph/example/quick_tour.cpp
// Modifications for clarity by Mark Fontenot

using namespace boost;

template < class Graph > struct exercise_vertex
{
    //state vars
    Graph& g;
    const char* name;

    //Constructor
    exercise_vertex(Graph& g_, const char name_[]) : g(g_), name(name_) {}

    //vertex descriptor
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    void operator()(const Vertex& v) const
    {
        typename property_map< Graph, vertex_index_t >::type vertex_id
                = get(vertex_index, g);
        std::cout << "vertex: " << name[get(vertex_id, v)] << std::endl;

        // Write out the outgoing edges
        std::cout << "\tout-edges: ";
        typename graph_traits< Graph >::out_edge_iterator out_i, out_end;
        typename graph_traits< Graph >::edge_descriptor e;
        for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i)
        {
            e = *out_i;
            Vertex src = source(e, g), targ = target(e, g);
            std::cout << "(" << name[get(vertex_id, src)] << ","
                      << name[get(vertex_id, targ)] << ") ";
        }
        std::cout << std::endl;

        // Write out the incoming edges
        std::cout << "\tin-edges: ";
        typename graph_traits< Graph >::in_edge_iterator in_i, in_end;
        for (boost::tie(in_i, in_end) = in_edges(v, g); in_i != in_end; ++in_i)
        {
            e = *in_i;
            Vertex src = source(e, g), targ = target(e, g);
            std::cout << "(" << name[get(vertex_id, src)] << ","
                      << name[get(vertex_id, targ)] << ") ";
        }
        std::cout << std::endl;

        // Write out all adjacent vertices
        std::cout << "\tadjacent vertices: ";
        typename graph_traits< Graph >::adjacency_iterator ai, ai_end;
        for (boost::tie(ai, ai_end) = adjacent_vertices(v, g); ai != ai_end;
             ++ai)
            std::cout << name[get(vertex_id, *ai)] << " ";
        std::cout << std::endl;
    }

};

void example_02()
{
    // create a typedef for the Graph_type type
    typedef adjacency_list< vecS, vecS, bidirectionalS, no_property,
            property< edge_weight_t, float > >
            Graph_type;

    // Make convenient labels for the vertices
    enum
    {
        A,
        B,
        C,
        D,
        E,
        N
    };
    const int num_vertices = N;
    const char name[] = "ABCDE";

    // writing out the edges in the graph
    typedef std::pair< int, int > Edge;
    Edge edge_array[] = {
            Edge(A, B),
            Edge(A, D),
            Edge(C, A),
            Edge(D, C),
            Edge(C, E),
            Edge(B, D),
            Edge(D, E),
    };
    const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

    // average transmission delay (in milliseconds) for each connection
    float transmission_delay[] = { 1.2, 4.5, 2.6, 0.4, 5.2, 1.8, 3.3, 9.1 };

    // declare a graph object, adding the edges and edge properties
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
    // VC++ can't handle the iterator constructor
    Graph_type g(num_vertices);
    property_map< Graph_type, edge_weight_t >::type weightmap = get(edge_weight, g);
    for (std::size_t j = 0; j < num_edges; ++j)
    {
        graph_traits< Graph_type >::edge_descriptor e;
        bool inserted;
        boost::tie(e, inserted)
            = add_edge(edge_array[j].first, edge_array[j].second, g);
        weightmap[e] = transmission_delay[j];
    }
#else
    Graph_type g(edge_array, edge_array + num_edges, transmission_delay, num_vertices);
#endif

//    typedef boost::property_map< Graph_type, vertex_index_t>::type a_special_typedef;
//    a_special_typedef vertex_id

    /** get all the vertices from graph g
     *
     *  note that the 'get' function is 1) global and 2) overloaded to operate
     *  on different types, the adjacency list object in these cases.
     */

    boost::property_map< Graph_type, vertex_index_t >::type vertex_id
            = get(vertex_index, g);

    /**
     * get all the edge weights from the graph g
     */
    boost::property_map< Graph_type, edge_weight_t >::type trans_delay
            = get(edge_weight, g);

    /**
     * print out the vertices using a vertex iterator
     */
    std::cout << "vertices(g) = ";

    //create the vertex iterator for graph type
    typedef graph_traits< Graph_type >::vertex_iterator vertex_iter;

    //the vertices(..) function returns a pair of iterators... first is
    //the start, second is the end. we use those in the loop
    std::pair< vertex_iter, vertex_iter > vp;
    typedef graph_traits <Graph_type>::vertex_descriptor Vertex;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
        Vertex v = *vp.first;
        std::cout << vertex_id[v] << " ";
//        std::cout << name[get(vertex_id, *vp.first)] << " ";
    }
    std::cout << std::endl << std::endl;

    //another way using boost::tie
    std::cout << "Another way to print vertices... " << std::endl;
    vertex_iter v_start, v_end;
    for(boost::tie(v_start, v_end) = vertices(g); v_start != v_end; ++v_start) {
        Vertex v = *v_start;
        std::cout << vertex_id[v] << " ";
    }
    std::cout << std::endl << std::endl;

    /**
     * print out each of the edges using an edge iterator
     */
    std::cout << "edges(g) = ";

    //typedef for edge descriptor for each edge
    typedef graph_traits< Graph_type >::edge_descriptor Edge_info;

    // create two iterators that will be the return value of edges(g)
    graph_traits< Graph_type >::edge_iterator ei_start, ei_end;

    for (boost::tie(ei_start, ei_end) = edges(g); ei_start != ei_end; ++ei_start) {
        Edge_info e = *ei_start;
        Vertex src = source(e, g);
        Vertex tgt = target(e, g);
        std::cout << "(" << vertex_id[src] << ", " << vertex_id[tgt] << ") ";
//        std::cout << "(" << name[get(vertex_id, source(*ei_start, g))] << ","
//                  << name[get(vertex_id, target(*ei_start, g))] << ") ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Printing vertices using a for_each loop and a lambda...\n";
    std::for_each(vertices(g).first, vertices(g).second, [](const Vertex& v){ std::cout << v << " ";});
    std::cout << std::endl << std::endl;


    /**
     * Using a for_each loop to process each vertex of the graph
     */
    std::for_each(vertices(g).first, vertices(g).second, exercise_vertex< Graph_type >(g, name));

    std::map< std::string, std::string > graph_attr, vertex_attr, edge_attr;
    graph_attr["size"] = "3,3";
    graph_attr["rankdir"] = "LR";
    graph_attr["ratio"] = "fill";
    vertex_attr["shape"] = "circle";

    boost::write_graphviz(std::cout, g, make_label_writer(name),
                          make_label_writer(trans_delay),
                          make_graph_attributes_writer(graph_attr, vertex_attr, edge_attr));

}