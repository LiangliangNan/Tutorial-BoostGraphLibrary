/*
*	Copyright (C) 2015 by Liangliang Nan (liangliang.nan@gmail.com)
*	https://3d.bk.tudelft.nl/liangliang/
*
*	This file is part of Easy3D: software for processing and rendering
*   meshes and point clouds.
*
*	Easy3D is free software; you can redistribute it and/or modify
*	it under the terms of the GNU General Public License Version 3
*	as published by the Free Software Foundation.
*
*	Easy3D is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "graph.h"


// This example shows how to use the powerful boost graph library

int main(int /*argc*/, char** /*argv*/) {
    // create an instance of Graph
    Graph graph;

    // we first add some vertices (in this simple example only three vertices),
    // then we connect them by an edge. The graph looks like:
    //
    //                  v0
    //                  ------------ v1
    //                              /
    //                            /
    //                          /
    //                        /
    //                       v2
    //
    //-----------------------------------------------------------------------
    //  add a vertex to the Graph: add_vertex()
    //-----------------------------------------------------------------------
    VertexProperty vp0;
    vp0.value = 0;
    VertexDescriptor vd0 = boost::add_vertex(vp0, graph);

    VertexProperty vp1;
    vp1.value = 1;
    VertexDescriptor vd1 = boost::add_vertex(vp1, graph);

    VertexProperty vp2;
    vp2.value = 2;
    VertexDescriptor vd2 = boost::add_vertex(vp2, graph);

    //-----------------------------------------------------------------------
    //  add an edge to the Graph: add_vertex()
    //-----------------------------------------------------------------------
    EdgeProperty ep01; // the edge connecting vertex 0 and 1
    ep01.weight = 10.0f;
    // in the returned value 'status', status.first will be the edge descriptor if status.second == ture
    std::pair<EdgeDescriptor, bool> status01 = boost::add_edge(vd0, vd1, ep01, graph);
    EdgeDescriptor ed01 = status01.first; // this is how to access the returned edge descriptor

    EdgeProperty ep12; // the edge connecting vertex 1 and 2
    ep12.weight = 20.0f;
    std::pair<EdgeDescriptor, bool> status12 = boost::add_edge(vd1, vd2, ep12, graph);
    EdgeDescriptor ed12 = status12.first; // this is how to access the returned edge descriptor

    //-----------------------------------------------------------------------
    //  access the vertex property given the vertex descriptor
    //-----------------------------------------------------------------------
    const VertexProperty& vp = graph[vd0];  // the vertex property of vertex 0

    //-----------------------------------------------------------------------
    //  access the edge property given the edge descriptor
    //-----------------------------------------------------------------------
    const EdgeProperty& ep = graph[ed01];  // property of the edge between vertex 0 and 1

    //-----------------------------------------------------------------------
    //  traverse all the vertices of a graph
    //-----------------------------------------------------------------------
    std::pair<VertexIterator, VertexIterator> vi = boost::vertices(graph);
    for (VertexIterator vit = vi.first; vit != vi.second; ++vit) {
        VertexDescriptor vd = *vit;             // vd is the vertex descriptor
        const VertexProperty&  vp = graph[vd];  // vp is the vertex property
        std::cout << "vertex value: " << vp.value << std::endl;
     }

    //-----------------------------------------------------------------------
    //  traverse all the edges of a graph
    //-----------------------------------------------------------------------
    std::pair<EdgeIterator, EdgeIterator> ei = boost::edges(graph);
    for (EdgeIterator eit = ei.first; eit != ei.second; ++eit) {
       EdgeDescriptor  ed = *eit;               // ed is the edge descriptor
       const EdgeProperty&  ep = graph[ed];     // ep is the edge property
       std::cout << "edge weight: " << ep.weight << std::endl;
    }

    //-----------------------------------------------------------------------
    //  access the two vetices connected by an edge given the edge descriptor
    //-----------------------------------------------------------------------
    VertexDescriptor sd = source(ed12, graph);
    VertexDescriptor td = target(ed12, graph);
    const VertexProperty& s_vp = graph[sd]; // the vertex property of the source vertex
    const VertexProperty& t_vp = graph[td]; // the vertex property of the target vertex
    std::cout << "source vertex of the edge12: " << s_vp.value << std::endl;
    std::cout << "target vertex of the edge12: " << t_vp.value << std::endl;

    //-----------------------------------------------------------------------
    //  check if two vertices are connected by an edge
    //-----------------------------------------------------------------------
    std::pair<EdgeDescriptor, bool> test = boost::edge(vd0, vd2, graph);
    if (test.second == true) {
        EdgeDescriptor ed = test.first;
        const EdgeProperty&  ep = graph[ed];
        std::cout << "vertex 0 and 2 are connected by an edge. The edge weight is: " << ep.weight << std::endl;
     }
    else {
        EdgeDescriptor ed = test.first;
        const EdgeProperty&  ep = graph[ed];
        std::cout << "vertex 0 and 2 are not connected by an edge." << std::endl;
    }

    test = boost::edge(vd1, vd2, graph);
    if (test.second == true) {
        EdgeDescriptor ed = test.first;
        const EdgeProperty&  ep = graph[ed];
        std::cout << "vertex 1 and 2 are connected by an edge. The edge weight is: " << ep.weight << std::endl;
     }
    else {
        EdgeDescriptor ed = test.first;
        const EdgeProperty&  ep = graph[ed];
        std::cout << "vertex 1 and 2 are not connected by an edge." << std::endl;
    }

    //-----------------------------------------------------------------------
    //  access the neighboring vertices of a vertex
    //-----------------------------------------------------------------------
    std::pair<AdjacencyIterator, AdjacencyIterator> adj_iter = boost::adjacent_vertices(vd1, graph);
    for (AdjacencyIterator ait = adj_iter.first; ait != adj_iter.second; ++ait) {
        VertexDescriptor vd = *ait;
        const VertexProperty&  vp = graph[vd];
        std::cout << "the vertex adjacent to vertex 1 has a value: " << vp.value << std::endl;
     }

    return EXIT_SUCCESS;
}
