/*
 * graph_tests.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cchet
 */
#include <string>
#include <iostream>
#include <cassert>
#include "graph.h"

using namespace std;
using namespace graph;

int main(int argc, char** argv) {
	Graph* graph = new Graph(10, true);
	Vertex* nullVertex = nullptr;
	Vertex* unmanagedVertex = new Vertex("unmanaged vertex node");

	////////////////////////////////////////////////////
	// invalid argument tests                         //
	////////////////////////////////////////////////////
	/*case 1: */
	cout << "Case 1.:  maxSize == 0" << endl << flush;
	Graph* case1_graph = new Graph(0);
	delete case1_graph;

	/* case 2: */
	cout << endl << "Case 2.:  maxSize == -1" << endl << flush;
	Graph* case2_graph = new Graph(-1);
	delete case2_graph;

	/* case 3: */
	cout << endl << "Case 3.:  printDepthFirst, null vertex" << endl << flush;
	graph->printDepthFirst(nullVertex);

	/* case 3: */
	cout << endl << "Case 3.:  printDepthFirst, unmanaged vertex" << endl
			<< flush;
	graph->printDepthFirst(unmanagedVertex);

	/* case 4: */
	cout << endl << "Case 3.:  printBreadthFirst, null vertex" << endl << flush;
	graph->printBreadthFirst(nullVertex);

	/* case 4: */
	cout << endl << "Case 3.:  printBreadthFirst, unmanaged vertex" << endl
			<< flush;
	graph->printBreadthFirst(unmanagedVertex);

	/* case 5: */
	cout << endl << "Case 5.:  hasCycles, empty graph" << endl << flush;
	graph->hasCycles();

	/* case 6: */
	cout << endl << "Case 6.:  addVertex, null vertex" << endl << flush;
	graph->addVertex(nullVertex);

	/* case 7: */
	cout << endl << "Case 7.:  addVertex, maxSize exceeded" << endl << flush;
	Graph* case7_graph = new Graph(1, true);
	Vertex* case7_1_vertex = new Vertex("case7_1_vertex");
	Vertex* case7_2_vertex = new Vertex("case7_2_vertex");
	case7_graph->addVertex(case7_1_vertex);
	case7_graph->addVertex(case7_2_vertex);
	// cleanup
	case7_graph->clear();
	case7_1_vertex = nullptr;
	case7_2_vertex = nullptr;
	delete case7_graph;

	/* case 8: */
	cout << endl << "Case 8.:  addEdge, null start node" << endl << flush;
	graph->addEdge(nullVertex, unmanagedVertex, 10);

	/* case 9: */
	cout << endl << "Case 9.:  addEdge, null end node" << endl << flush;
	graph->addEdge(unmanagedVertex, nullVertex, 10);

	/* case 10: */
	cout << endl << "Case 10.:  addEdge, unmanaged nodes" << endl << flush;
	Vertex* case10_1_vertex = new Vertex("case10_1_vertex");
	graph->addVertex(case10_1_vertex);
	graph->addEdge(unmanagedVertex, unmanagedVertex, 10);
	// cleanup
	graph->clear();
	case10_1_vertex = nullptr;

	////////////////////////////////////////////////////
	// valid tests                                    //
	////////////////////////////////////////////////////
	/* case 11: */
	cout << endl << "Case 11.:  operator<<" << endl << flush;
	Vertex* case11_1_vertex = new Vertex("case11_1_vertex");
	Vertex* case11_2_vertex = new Vertex("case11_2_vertex");
	Vertex* case11_3_vertex = new Vertex("case11_3_vertex");
	graph->addVertex(case11_1_vertex);
	graph->addVertex(case11_2_vertex);
	graph->addVertex(case11_3_vertex);
	cout << *graph << flush;
	graph->clear();

	/* case 12, 13, 14: */
	cout << endl << "Case 13 - 14:  prepared graph after vertex/aedge adding" << endl << flush;
	Vertex* case12_1_vertex = new Vertex("case12_1_vertex");
	Vertex* case12_2_vertex = new Vertex("case12_2_vertex");
	Vertex* case12_3_vertex = new Vertex("case12_3_vertex");
	graph->addVertex(case12_1_vertex);
	graph->addVertex(case12_2_vertex);
	graph->addVertex(case12_3_vertex);
	cout << endl << "After Vertex addition (operator<<)" << endl << *graph << flush;

	graph->addEdge(case12_1_vertex, case12_1_vertex, 1);
	graph->addEdge(case12_2_vertex, case12_3_vertex, 1);
	graph->addEdge(case12_1_vertex, case12_3_vertex, 1);
	graph->addEdge(case12_3_vertex, case12_1_vertex, 1);
	cout << endl << "After Edge addition (operator<<)" << endl << *graph << flush;

	/* case 12: */
	cout << endl << "Case 12.:  printDepthFirst(case12_1_vertex)" << endl << flush;
	graph->printDepthFirst(case12_1_vertex);

	/* case 13: */
	cout << endl << "Case 13.:  printDepthFirst(case12_2_vertex)" << endl << flush;
	graph->printDepthFirst(case12_2_vertex);

	/* case 13: */
	cout << endl << "Case 13.:  printBreadthFirst(case12_1_vertex)" << endl << flush;
	graph->printBreadthFirst(case12_1_vertex);

	/* case 14: */
	cout << endl << "Case 14.:  printBreadthFirst(case12_2_vertex)" << endl << flush;
	graph->printBreadthFirst(case12_2_vertex);

	/* case 15: */
	cout << endl << "Case 15.:  former graph hasCycles == true" << endl << flush;
	assert(graph->hasCycles());
	graph->clear();

	/* case 16: */
	cout << endl << "Case 16.:  hasCycles == false" << endl << flush;
	Vertex* case16_1_vertex = new Vertex("case16_1_vertex");
	Vertex* case16_2_vertex = new Vertex("case16_2_vertex");
	Vertex* case16_3_vertex = new Vertex("case16_3_vertex");
	graph->addVertex(case16_1_vertex);
	graph->addVertex(case16_2_vertex);
	graph->addVertex(case16_3_vertex);
	cout << endl << "Added vertex (operator<<)" << endl << *graph << flush;
	graph->addEdge(case16_1_vertex, case16_2_vertex, 1);
	graph->addEdge(case16_1_vertex, case16_3_vertex, 1);
	graph->addEdge(case16_2_vertex, case16_3_vertex, 1);
	cout << endl << "Added Edge (operator<<)" << endl << *graph << flush;
	assert(!graph->hasCycles());

	// clear
	graph->clear();
	delete graph;

	cout << "" << endl << flush;
}

