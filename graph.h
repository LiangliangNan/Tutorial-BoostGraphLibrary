#ifndef BOOST_GRAPH_H
#define BOOST_GRAPH_H

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

// The graph data structure.
// Here we inherit the Graph class from the boost::adjacency_list,
// allowing easier forward declaration.
class Graph : public boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty>
{
public:
    Graph() {}
    ~Graph() {}
};

// vertex descriptor (from which you can access the vertex property)
typedef boost::graph_traits<Graph>::vertex_descriptor   VertexDescriptor;
// edge descriptor (from which you can access the edge property)
typedef boost::graph_traits<Graph>::edge_descriptor     EdgeDescriptor;

// vertex iterator (from which you can traverse all the vertices of a graph)
typedef boost::graph_traits<Graph>::vertex_iterator     VertexIterator;
// edge iterator (from which you can traverse all the edges of a graph)
typedef boost::graph_traits<Graph>::edge_iterator       EdgeIterator;

// adjacent vertex iterator (from which you can traverse the adjacent vertices of a vertex)
typedef boost::graph_traits<Graph>::adjacency_iterator  AdjacentVertexIterator;
// incident edge iterator (from which you can traverse the incident edges radiating from a vertex)
typedef boost::graph_traits<Graph>::out_edge_iterator   OutEdgeIterator;


#endif


