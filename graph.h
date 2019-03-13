#ifndef GRAPH_H
#define GRAPH_H

// include the boost graph header file
#include <boost/graph/adjacency_list.hpp>


// VertexProperty: the data to be stored for each vertex.
// In this simple example, it stores only an integer value.
struct VertexProperty {
    int    value;
};

// EdgeProperty: the data to be stored for each edge.
// In this simple example, it stores only an floating point number.
struct EdgeProperty {
    float  weight;
};

// this is the graph
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> Graph;

// vertex/edge descriptor (from which you can access the vertex/edge properties)
typedef boost::graph_traits<Graph>::vertex_descriptor   VertexDescriptor;
typedef boost::graph_traits<Graph>::edge_descriptor     EdgeDescriptor;

// vertex/edge iterators (from which you can traverse all the vertices/edges of the graph)
typedef boost::graph_traits<Graph>::vertex_iterator     VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator       EdgeIterator;

// vertex/edge adjacency iterators (from which you can traverse all the adjacency information)
typedef boost::graph_traits<Graph>::adjacency_iterator  AdjacencyIterator;
typedef boost::graph_traits<Graph>::out_edge_iterator   OutEdgeIterator;


#endif


