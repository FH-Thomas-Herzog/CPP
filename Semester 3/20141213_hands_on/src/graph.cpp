/*
 * edge.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: cchet
 */
#include "graph.h"
#include <iostream>
#include <ostream>
#include <algorithm>

using namespace std;

namespace graph {
	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	Graph::Graph(const int maxSize) :
			maxSize(maxSize) {

		/* Init first dimension */
		matrix = (double**) malloc(maxSize * sizeof(double**));
		if (matrix == nullptr) {
			exit(EXIT_FAILURE);
		} /* if */

		/* Init second dimension */
		for (int i = 0; i < maxSize; ++i) {
			matrix[i] = (double*) malloc(maxSize * sizeof(double*));
			if (matrix == nullptr) {
				exit(EXIT_FAILURE);
			} /* if */
		} /* for */

		/* set all edge values to 0 */
		clearEdges();

		/* Init the nodes vector */
		nodes.reserve(maxSize);
	}

	Graph::~Graph() {
		clearEdges();
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
		int idx = -1;

		if (!nodes.empty()) {
			idx = 0;
			while ((idx < nodes.size()) && (nodes[idx] != node)) {
				idx++;
			}
			idx = (idx == nodes.size()) ? -1 : idx;
		} /* if */

		return idx;
	}

	bool Graph::hasCycles(Vertex* node, vector<Vertex*>* visited) const {
		bool invalid = false;

		/* add to call stack */
		visited->push_back(node);

		if ((find(visited->begin(), visited->end(), node) == visited->end())) {
			/* get first connected vertex index */
			int colIdx = 0;
			int rowIdx = getIdxForVertex(node);
			while ((!invalid) && (colIdx < nodes.size())) {
				/* visit next child */
				if (matrix[rowIdx][colIdx] != 0) {
					invalid = hasCycles(nodes[colIdx], visited);
				} /* if */
				colIdx++;
			} /* while */
		} else {
			invalid = true;
		} /* if */

		/* remove from call stack */
		visited->pop_back();

		return invalid;
	}

	void Graph::deepTraversePrint(Vertex* node,
			vector<Vertex*>* visited) const {
		/* add to call stack */
		visited->push_back(node);

		/* anchor for already visited */
		if ((find(visited->begin(), visited->end(), node) == visited->end())) {
			/* get first connected vertex index */
			int rowIdx = getIdxForVertex(node);
			for (int i = 0; i < nodes.size(); ++i) {
				/* visit next child */
				if (matrix[rowIdx][i] != 0) {
					deepTraversePrint(nodes[i], visited);
				} /* if */
			} /* while */
			cout << "Visited: " << *node << endl << flush;
		} /* if */

		/* remove from call stack */
		visited->pop_back();
	}

	void Graph::breathTraversePrint(Vertex* node,
			vector<Vertex*>* visited) const {
		/* add to call stack */
		visited->push_back(node);

		/* anchor for already visited */
		if ((find(visited->begin(), visited->end(), node) == visited->end())) {

			/* print visited */
			cout << "Parent: " << *node << endl << flush;

			/* get first connected vertex index */
			int rowIdx = getIdxForVertex(node);
			vector<Vertex*> toVisitVector;
			for (int i = 0; i < nodes.size(); ++i) {
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
		}

		/* remove from call stack */
		visited->pop_back();
	}

	bool Graph::isValidVertex(const Vertex* node) const {
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
		/* Add if not already present */
		if (find(nodes.begin(), nodes.end(), node) != nodes.end()) {
			cout << "vertex already present !!! Adding aborted" << endl
					<< flush;
		} else {
			cout << "Vertex node added !!! node.name: " << node->name << endl;
			nodes.push_back(node);
		} /* if */
	}

	void Graph::addEdge(const Vertex* startNode, const Vertex* endNode,
			double weight) {
		int rowIdx, colIdx;

		rowIdx = this->getIdxForVertex(startNode);
		colIdx = this->getIdxForVertex(endNode);

		/* Check if vertex nodes are hold by backed container */
		if ((rowIdx < 0) || (colIdx < 0)) {
			cout << "Vertex instance not hold by backed container !!! start="
					<< startNode->name << " | end=" << endNode->name << endl
					<< flush;
		} else {
			matrix[rowIdx][colIdx] = weight;
		} /* if */
	}

	void Graph::clearEdges() {
		for (int i = 0; i < maxSize; i++) {
			for (int j = 0; j < maxSize; j++) {
				matrix[i][j] = 0;
			} /* for */
		} /* for */
	}

	void Graph::clear() {
		clearEdges();

		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			delete (*it);
		} /* for */

		nodes.clear();
	}

	void Graph::printDepthFirst(const Vertex* start) const {
		if (isValidVertex(start)) {
			/* prepare call stack */
			vector<Vertex*> visited;

			/* start recursion */
			deepTraversePrint(nodes[getIdxForVertex(start)], &visited);
		} /* if */
	}

	void Graph::printBreadthFirst(const Vertex* start) const {
		if (isValidVertex(start)) {
			/* prepare call stack */
			vector<Vertex*> visited;

			/* start recursion */
			breathTraversePrint(nodes[getIdxForVertex(start)], &visited);
		} /* if */
	}

	bool Graph::hasCycles() const {
		int i = 0;
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
		os << "print graph:" << endl;
		for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
			os << "node: " << (*it)->name << endl;
			for (int j = 0; j < graph.nodes.size(); ++j) {
				if (graph.matrix[i][j] != 0) {
					os << "     related node: " << (**it) << "("
							<< graph.matrix[i][j] << ")" << endl;
				} /* if */
			} /* for */
			i++;
		} /* for */

		return os;
	}
}
