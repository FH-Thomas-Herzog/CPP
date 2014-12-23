/*
 * edge.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: Thomas Herzog
 *
 *      This class contains the graph implementation of the graph.h specification.
 */
#include "graph.h"
#include <iostream>
#include <ostream>
#include <algorithm>
#include <cassert>

using namespace std;

namespace graph {
	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	Graph::Graph(const int maxSize) :
			Graph(maxSize, false) {
	}

	Graph::Graph(const int maxSize, bool log) :
			maxSize(maxSize), log(log) {

		/* log constructor call */
		if (log) {
			cout << "constructor (" << maxSize << ", " << log << ") called"
					<< endl << flush;
		}
		/* validate maxSize */
		if (maxSize <= 0) {
			this->maxSize = 10;
			cout << "invalid maxSize !!! default set to '10'" << endl << flush;

		}

		/* Init first dimension */
		matrix = (double**) malloc(this->maxSize * sizeof(double**));
		if (matrix == nullptr) {
			exit(EXIT_FAILURE);
		} /* if */

		/* Init second dimension */
		for (int i = 0; i < this->maxSize; ++i) {
			matrix[i] = (double*) malloc(this->maxSize * sizeof(double*));
			if (matrix == nullptr) {
				exit(EXIT_FAILURE);
			} /* if */
		} /* for */

		/* set all edge values to 0 */
		clearEdges();

		/* Init the nodes vector */
		nodes.reserve(this->maxSize);
	}

	Graph::~Graph() {
		/* log destructor call */
		if (log) {
			cout << "destructor () called." << endl << flush;
		}

		/* delete vertex nodes */
		clear();

		/* delete matrix */
		for (int i = 0; i < maxSize; i++) {
			free(matrix[i]);
			matrix[i] = nullptr;
		} /* for */
		free(matrix);
		matrix = nullptr;
	}

	////////////////////////////////////////////////////////////
	// Private methods                                        //
	////////////////////////////////////////////////////////////
	int Graph::getIdxForVertex(const Vertex* node) const {
		size_t idx = -1;

		if (!nodes.empty()) {
			idx = 0;
			while ((idx < nodes.size()) && (nodes[idx] != node)) {
				idx++;
			} /* while */
			idx = (idx == nodes.size()) ? -1 : idx;
		} /* if */

		return idx;
	}

	bool Graph::hasCycles(Vertex* node, vector<Vertex*>* visited) const {
		bool invalid = false;

		if ((find(visited->begin(), visited->end(), node) == visited->end())) {
			/* add to call stack */
			visited->push_back(node);

			/* get first connected vertex index */
			size_t colIdx = 0;
			int rowIdx = getIdxForVertex(node);
			while ((!invalid) && (colIdx < nodes.size())) {
				/* visit next child */
				if (matrix[rowIdx][colIdx] != 0) {
					invalid = hasCycles(nodes[colIdx], visited);
				} /* if */
				colIdx++;
			} /* while */

			/* remove from call stack */
			visited->pop_back();
		} else {
			invalid = true;
		} /* if */


		return invalid;
	}

	void Graph::deepTraversePrint(Vertex* node,
			vector<Vertex*>* visited) const {

		/* anchor for already visited */
		if ((find(visited->begin(), visited->end(), node) == visited->end())) {
			/* add to call stack */
			visited->push_back(node);

			/* print node */
			cout << "Visited: " << *node << endl << flush;

			/* get first connected vertex index */
			int rowIdx = getIdxForVertex(node);
			for (size_t i = 0; i < nodes.size(); ++i) {
				/* visit next child */
				if (matrix[rowIdx][i] != 0) {
					deepTraversePrint(nodes[i], visited);
				} /* if */
			} /* while */

			/* remove from call stack */
			visited->pop_back();

		} /* if */
	}

	void Graph::breathTraversePrint(Vertex* node,
			vector<Vertex*>* visited) const {

		/* anchor for already visited */
		if ((find(visited->begin(), visited->end(), node) == visited->end())) {

			/* add to call stack */
			visited->push_back(node);

			/* print visited */
			cout << "Parent: " << *node << endl << flush;

			/* get first connected vertex index */
			int rowIdx = getIdxForVertex(node);
			vector<Vertex*> toVisitVector;
			for (size_t i = 0; i < nodes.size(); ++i) {
				/* visit next child */
				if (matrix[rowIdx][i] != 0) {
					Vertex* curNode = nodes[i];
					toVisitVector.push_back(curNode);
					cout << "     Child: " << *curNode << endl << flush;
				} /* if */
			} /* for */

			/* visit the next level */
			for (auto it = toVisitVector.begin(); it != toVisitVector.end();
					it++) {
				breathTraversePrint((*it), visited);
			} /* for */

			/* clear stack */
			toVisitVector.clear();

			/* remove from call stack */
			visited->pop_back();
		}
	}

	bool Graph::isManagedVertex(const Vertex* node) const {
		/* start is null */
		if (node == nullptr) {
			cout << "start vertex is null !!! Cannot print graph on null vertex"
					<< endl << flush;
			return false;
		}
		/* start not part of graph */
		else if (getIdxForVertex(node) == -1) {
			cout << "given start is not part of this graph !!!" << endl
					<< flush;
			return false;
		} /* if */

		return true;
	}

	////////////////////////////////////////////////////////////
	// Public methods                                         //
	////////////////////////////////////////////////////////////
	void Graph::addVertex(Vertex* node) {
		/* null node*/
		if (node == nullptr) {
			cout << "cannot add null vertex node !!!" << endl << flush;
			return;
		}
		/* node already  present in vector (pointer address) */
		if (find(nodes.begin(), nodes.end(), node) != nodes.end()) {
			cout << "vertex already present !!! Adding aborted" << endl
					<< flush;
			return;
		}
		/* container already full */
		else if (nodes.size() == size_t(maxSize)) {
			cout << "maxSize exceeded !!!" << endl << flush;
			return;
		}
		/* add node */
		else {
			nodes.push_back(node);
		} /* if */
	}

	void Graph::addEdge(const Vertex* startNode, const Vertex* endNode,
			double weight) {
		int rowIdx, colIdx;

		/* null vertex */
		if ((startNode == nullptr) || ((endNode == nullptr))) {
			cout << "start and end node are not allowed to be null !!!" << endl
					<< flush;
			return;
		}
		/* no vertex node present */
		else if (nodes.size() == 0) {
			cout << "no vertex nodes present !!!" << endl << flush;

			return;
		}
		/* invalid weight */
		else if (weight <= 0) {
			cout << "invalid weight !!! 0 < weight < DOUBLE_MAX";

			return;
		} /* if */

		/* get intended indices */
		rowIdx = getIdxForVertex(startNode);
		colIdx = getIdxForVertex(endNode);

		/* vertex instance not managed */
		if ((rowIdx < 0) || (colIdx < 0)) {
			cout << "Vertex instance not hold by backed container !!! start="
					<< startNode->name << " | end=" << endNode->name << endl
					<< flush;

			return;
		}
		/* add edge */
		else {
			matrix[rowIdx][colIdx] = weight;
		} /* if */
	}

	void Graph::clearEdges() {
		/* delete all edge weights */
		for (int i = 0; i < maxSize; i++) {
			for (int j = 0; j < maxSize; j++) {
				matrix[i][j] = 0;
			} /* for */
		} /* for */
	}

	void Graph::clear() {
		/* remove all edges */
		clearEdges();

		/* remove all vertex nodes */
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			delete (*it);
		} /* for */

		/* empty vector */
		nodes.clear();
	}

	void Graph::printDepthFirst(const Vertex* start) const {
		/* is vertex instance managed */
		if (isManagedVertex(start)) {

			/* prepare call stack */
			vector<Vertex*> visited;

			/* start recursion */
			deepTraversePrint(nodes[getIdxForVertex(start)], &visited);
		} /* if */

	}

	void Graph::printBreadthFirst(const Vertex* start) const {
		/* is vertex instance managed */
		if (isManagedVertex(start)) {

			/* prepare call stack */
			vector<Vertex*> visited;

			/* start recursion */
			breathTraversePrint(nodes[getIdxForVertex(start)], &visited);
		} /* if */

	}

	bool Graph::hasCycles() const {
		/* vertex node presents */
		if (nodes.size() == 0) {
			cout << "cannot determine cycles on empty graph" << endl << flush;
			return false;
		}

		size_t i = 0;
		bool cyclic = false;

		/* Walk through all nodes  */
		while ((i < nodes.size()) && (!cyclic)) {
			/* prepare call stack */
			vector<Vertex*> visited;

			cyclic = hasCycles(nodes[i], &visited);

			i++;
		} /* while */

		return cyclic;
	}

////////////////////////////////////////////////////////////
// friend methods                                         //
////////////////////////////////////////////////////////////
	ostream& operator<<(ostream& os, const Graph& graph) {
		int i = 0;
		/* introduce graph printing */
		os << "print graph:" << endl;
		/* iterate via present vertex nodes in the graph */
		for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
			os << i << ". node: " << (*it)->name << endl;
			for (size_t j = 0; j < graph.nodes.size(); ++j) {
				if (graph.matrix[i][j] != 0) {
					os << "     related node: " << (*graph.nodes[j]) << "("
							<< graph.matrix[i][j] << ")" << endl;
				} /* if */
			} /* for */
			i++;
		} /* for */

		return os;
	}
}
