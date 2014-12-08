/*
 * graph.h
 *
 *  Created on: Dec 5, 2014
 *      Author: cchet
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>

using namespace std;

namespace graph {
	/**
	 * This class represents the graph nodes.
	 */
	class Vertex {

		public:
			////////////////////////////////////////////////////////////
			// Public members                                         //
			////////////////////////////////////////////////////////////
			const string name;

			////////////////////////////////////////////////////////////
			// Constructor and Destructor                             //
			////////////////////////////////////////////////////////////
			inline Vertex(const string name) :
					name(name) {
			}

			////////////////////////////////////////////////////////////
			// friend methods                                         //
			////////////////////////////////////////////////////////////
			inline friend ostream& operator<<(ostream& os,
					const Vertex& vertex) {
				os << vertex.name;
				return os;
			}
	};

	/**
	 * This class represents the graph
	 */
	class Graph {

		private:
			////////////////////////////////////////////////////////////
			// Private members                                        //
			////////////////////////////////////////////////////////////
			/**
			 * The matrix containing the edge weight information
			 */
			double** matrix;
			/**
			 * The vector containing all placed graph vertex nodes
			 */
			vector<Vertex*> nodes;

			////////////////////////////////////////////////////////////
			// Private methods                                        //
			////////////////////////////////////////////////////////////
			/**
			 * Gets the index of the vertex in the vector which is the same index as in the matrix (i = j).
			 *
			 * @param
			 * 		node the node the get its index
			 * @return
			 * 		the index of the node in the vector or -1 if the vertex instance is not hold by this graph.
			 */
			int getIdxForVertex(const Vertex* node) const;

			/**
			 * Recursively walks through the graph from the given start vertex node until it reaches the end o f
			 * the tree or it detects an recursion
			 *
			 * @param
			 * 		node the start node to traverse from
			 * @param
			 * 		visited the vector used as a stack for detecting already visited vertex nodes.
			 *
			 * @return
			 * 		true if the graph has cycles false otherwise
			 */
			bool hasCycles(Vertex* node, vector<Vertex*>* visited) const;

			/**
			 * Recursively walks through the graph by crawling to the last elements of the graph.
			 *
			 * @param
			 * 		node the node to start from
			 *
			 * @param
			 *		visited the vector used as a stack to detect cycles in the graph
			 */
			void deepTraversePrint(Vertex* node,
					vector<Vertex*>* visited) const;

			/**
			 * Recursively walks through the graph by visiting the all elements on the smae level before
			 * crawling to the next level.
			 *
			 * @param
			 * 		node the node to start from
			 *
			 * @param
			 *		visited the vector used as a stack to detect cycles in the graph
			 */
			void breathTraversePrint(Vertex* node,
					vector<Vertex*>* visited) const;

			/**
			 * Answers the question if the current visited vertex node is a valid vertex node and hold by this graph.
			 *
			 * @param
			 * 		node the node to be checked
			 *
			 * @return
			 * 		true if the vertex node is valid, false otherwise
			 */
			bool isValidVertex(const Vertex* node) const;

		public:
			////////////////////////////////////////////////////////////
			// Public members                                         //
			////////////////////////////////////////////////////////////
			const int maxSize;

			////////////////////////////////////////////////////////////
			// Constructor and Destructor                             //
			////////////////////////////////////////////////////////////
			Graph(const int maxSize);

			~Graph();

			////////////////////////////////////////////////////////////
			// Public methods                                         //
			////////////////////////////////////////////////////////////
			/**
			 * Adds a vertex node to the graph.
			 * This node will be added to the end of the matrix.
			 *
			 * @param
			 * 		node the node to be added
			 */
			void addVertex(Vertex* node);

			/**
			 * Adds a edge between two graph vertex nodes.
			 *
			 * @param
			 * 		startNode the vertex node which references a other node
			 * @param
			 * 		endNode the vertex node which is referenced by the start node
			 * @param
			 * 		weight the weight of the node
			 */
			void addEdge(const Vertex* startNode, const Vertex* endNode,
					double weight);

			/**
			 * Clears all edges of the graph which leaves teh vertex nodes unconnected to each other
			 */
			void clearEdges();

			/**
			 * Clears the graph by removing all edges nodes from the graph
			 */
			void clear();

			/**
			 * Prints the graph vertex nodes from the last level up
			 *
			 * @param
			 * 		start the vertex node to start from
			 */
			void printDepthFirst(const Vertex* start) const;

			/**
			 * Prints the graph vertex nodes from the top level down and prints all nodes on the same level before
			 * crawling to the next level
			 *
			 * @param
			 * 		start the vertex node to start from
			 */
			void printBreadthFirst(const Vertex* start) const;

			/**
			 * Answers the question if this graph has cycles or not.
			 *
			 * @return
			 * 		true if the graph has cycles false otherwise
			 */
			bool hasCycles() const;

			////////////////////////////////////////////////////////////
			// friend methods                                         //
			////////////////////////////////////////////////////////////
			friend ostream& operator<<(ostream& os, const Graph& graph);
	};
}

#endif /* GRAPH_H_ */
