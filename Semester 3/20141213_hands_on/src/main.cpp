/*
 * graph.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: cchet
 */

#include <string>
#include <iostream>
#include "graph.h"

using namespace std;
using namespace graph;

int main(int argc, char** argv) {
	Graph* graph = new Graph(10);
	Vertex* v1 = new Vertex("node_1");
	Vertex* v2 = new Vertex("node_2");
	Vertex* v3 = new Vertex("node_3");
	Vertex* v4 = new Vertex("node_4");
	graph->addVertex(v1);
	graph->addVertex(v2);
	graph->addVertex(v3);
	graph->addVertex(v4);
	cout << "no edges" << endl << *graph << endl << flush;

	Vertex* vertex = new Vertex("node_not_in_graph");
	graph->addEdge(vertex, vertex, 10);

	graph->addEdge(v1, v1, 10);
	graph->addEdge(v1, v2, 10);
	graph->addEdge(v1, v3, 10);
	graph->addEdge(v1, v4, 10);

	graph->addEdge(v2, v1, 10);
	graph->addEdge(v2, v2, 10);
	graph->addEdge(v2, v3, 10);
	graph->addEdge(v2, v4, 10);

	graph->addEdge(v3, v1, 10);
	graph->addEdge(v3, v2, 10);
	graph->addEdge(v3, v3, 10);
	graph->addEdge(v3, v4, 10);

	graph->addEdge(v4, v1, 10);
	graph->addEdge(v4, v2, 10);
	graph->addEdge(v4, v3, 10);
	graph->addEdge(v4, v4, 10);
	cout << "with edges" << endl << *graph << endl << flush;

	graph->printDepthFirst(v1);
	graph->printBreadthFirst(v1);

	cout << "Is graph cyclic: " << graph->hasCycles() << endl << flush;

	graph->clearEdges();
	cout << "cleared edges" << endl << *graph << endl << flush;
	graph->clear();
	cout << "cleared graph" << endl << *graph << endl << flush;

	return 0;
}
