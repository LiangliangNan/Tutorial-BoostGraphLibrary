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
    //    v0     10
    //    ------------ v1
    //                /
    //              /
    //            /  20
    //          /
    //         v2

    //-----------------------------------------------------------------------
    //  add a vertex to the Graph: add_vertex()
    //-----------------------------------------------------------------------
    VertexProperty vp0;
    vp0.value = 0;
    vp0.name = "v0";
    VertexDescriptor vd0 = boost::add_vertex(vp0, graph);
    std::cout << "added vertex " << vd0 << std::endl;

    VertexProperty vp1;
    vp1.value = 1;
    vp1.name = "v1";
    VertexDescriptor vd1 = boost::add_vertex(vp1, graph);
    std::cout << "added vertex " << vd1 << std::endl;

    VertexProperty vp2;
    vp2.value = 2;
    vp2.name = "v2";
    VertexDescriptor vd2 = boost::add_vertex(vp2, graph);
    std::cout << "added vertex " << vd2 << std::endl;

    //-----------------------------------------------------------------------
    //  add an edge to the Graph: add_vertex()
    //-----------------------------------------------------------------------
    EdgeProperty ep01; // the edge connecting vertex 0 and 1
    ep01.weight = 10.0f;
    // in the returned value 'status', status.first will be the edge descriptor if status.second == ture
    std::pair<EdgeDescriptor, bool> status01 = boost::add_edge(vd0, vd1, ep01, graph);
    EdgeDescriptor ed01 = status01.first; // this is how to access the returned edge descriptor
    if (status01.second)
        std::cout << "added edge " << ed01 << " connecting vertices " << vd0 << " and " << vd1 << std::endl;
    else
        std::cout << "failed to add an edge connecting vertices" << vd0 << " and " << vd1 << std::endl;

    EdgeProperty ep12; // the edge connecting vertex 1 and 2
    ep12.weight = 20.0f;
    std::pair<EdgeDescriptor, bool> status12 = boost::add_edge(vd1, vd2, ep12, graph);
    EdgeDescriptor ed12 = status12.first; // this is how to access the returned edge descriptor
    if (status12.second)
        std::cout << "added edge " << ed12 << " connecting vertices " << vd1 << " and " << vd2 << std::endl;
    else
        std::cout << "failed to add an edge connecting vertices" << vd1 << " and " << vd2 << std::endl;

    //-----------------------------------------------------------------------
    //  query the number of vertices in a graph
    //-----------------------------------------------------------------------
    std::cout << "number of vertices in the graph: " << boost::num_vertices(graph) << std::endl;

    //-----------------------------------------------------------------------
    //  query the number of edges in a graph
    //-----------------------------------------------------------------------
    std::cout << "number of edges in the graph: " << boost::num_edges(graph) << std::endl;

    //-----------------------------------------------------------------------
    //  traverse all the vertices of a graph
    //-----------------------------------------------------------------------
    std::pair<VertexIterator, VertexIterator> vi = boost::vertices(graph);
    for (VertexIterator vit = vi.first; vit != vi.second; ++vit) {
        VertexDescriptor vd = *vit;             // vd is the vertex descriptor
        //-----------------------------------------------------------------------
        //  access the vertex property given the vertex descriptor
        //-----------------------------------------------------------------------
        const VertexProperty&  vp = graph[vd];  // vp is the vertex property
        std::cout << "vertex " << vd << ": name is " << vp.name << ", value is " << vp.value << std::endl;
     }

    //-----------------------------------------------------------------------
    //  traverse all the edges of a graph
    //-----------------------------------------------------------------------
    std::pair<EdgeIterator, EdgeIterator> ei = boost::edges(graph);
    for (EdgeIterator eit = ei.first; eit != ei.second; ++eit) {
       EdgeDescriptor ed = *eit;               // ed is the edge descriptor
       //-----------------------------------------------------------------------
       //  access the edge property given the edge descriptor
       //-----------------------------------------------------------------------
       const EdgeProperty&  ep = graph[ed];     // ep is the edge property
       std::cout << "edge " << ed << ": weight is " << ep.weight << std::endl;
    }

    //-----------------------------------------------------------------------
    //  access the two vetices connected by an edge given the edge descriptor
    //-----------------------------------------------------------------------
    VertexDescriptor sd = source(ed12, graph);
    VertexDescriptor td = target(ed12, graph);
    std::cout << "source vertex of the edge " << ed12 << " is " << sd << std::endl;
    std::cout << "target vertex of the edge " << ed12 << " is " << td << std::endl;

    //-----------------------------------------------------------------------
    //  query the edge for a vertex pair.
    //  If the second element of the returned value is true, the edge exists and the first
    //  element carries the edge descriptor.
    //  If the second element of the returned value is false, the edge does not exists.
    //-----------------------------------------------------------------------
    std::pair<EdgeDescriptor, bool> test = boost::edge(vd0, vd2, graph);
    if (test.second == true) {
        EdgeDescriptor ed = test.first;
        std::cout << "vertex " << vd0 << " and " << vd2 << " are connected by the edge " << ed << std::endl;
     }
    else
        std::cout << "vertex " << vd0 << " and " << vd2 << " are not connected by an edge." << std::endl;

    test = boost::edge(vd1, vd2, graph);
    if (test.second == true) {
        EdgeDescriptor ed = test.first;
        std::cout << "vertex " << vd1 << " and " << vd2 << " are connected by the edge " << ed << std::endl;
     }
    else
        std::cout << "vertex " << vd1 << " and " << vd2 << " are not connected by an edge." << std::endl;

    //-----------------------------------------------------------------------
    //  access the neighboring vertices of a vertex
    //-----------------------------------------------------------------------
    std::cout << "neighboring vertices of vertex " << vd1 << ": ";
    std::pair<AdjacentVertexIterator, AdjacentVertexIterator> adj_v_iter = boost::adjacent_vertices(vd1, graph);
    for (AdjacentVertexIterator ait = adj_v_iter.first; ait != adj_v_iter.second; ++ait) {
        VertexDescriptor vd = *ait;
        std::cout << vd << " ";
    }
    std::cout << std::endl;

    //-----------------------------------------------------------------------
    //  access the incicent edges of a vertex
    //-----------------------------------------------------------------------
    std::cout << "incident edges of vertex " << vd1 << ": ";
    std::pair<OutEdgeIterator, OutEdgeIterator> adj_e_iter = boost::out_edges(vd1, graph);
    for (OutEdgeIterator ait = adj_e_iter.first; ait != adj_e_iter.second; ++ait) {
        EdgeDescriptor ed = *ait;
        std::cout << ed << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
