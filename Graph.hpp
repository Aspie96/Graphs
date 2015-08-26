/*
	Copyright (C) 2015 - Code written 100% by Valentino Giudice (valentino.giudice96@gmail.com)

	This work is dual-licensed:
	- under the Do What The Fuck You Want To Public License (version 2): http://www.wtfpl.net/
	- under the CC0 1.0 Universal Public Domain Dedication:              http://creativecommons.org/publicdomain/zero/1.0/

	Enjoy!
	If you want to contact me: valentino.giudice96@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <vector>
#include "GraphLink.hpp"
#include "GraphNode.hpp"

using namespace std;

template<typename T> class GraphLink;

/**
 * This is the main class of this library: it allows you to manage graphs and to apply the Dijkstra algorithm.
 *
 * @param   <T> The type of the content of the nodes contained in this graph.
 * @see     GraphNode
 * @author  Valentino Giudice
 */
template<typename T> class Graph {
	public:
		/**
		 * Creates a new empty graph.
		 */
		Graph();
		virtual ~Graph();

		/**
		 * Creates a new node and adds it to the graph.
		 *
		 * @param   item    The value of the node to be created.
		 * @return  A pointer to the created node.
		 */
		GraphNode<T> *add(T);

		/**
		 * Applies Dijkstra's algorithm to find the shortest path from one node to another.
		 *
		 * @param   node1   A pointer to the starting node (it must be a node of this graph, added with {@link #add(T)}).
		 * @param   node2   A pointer to the destination node (it must be a node of this graph, added with {@link #add(T)}).
		 * @return  The vector containing pointers to all the node to be passed by in order to get from the starting node to the destination one.
		 */
		vector<GraphLink<T>*> dijkstra(GraphNode<T>*, GraphNode<T>*);

		/**
		 * Applies Dijkstra's algorithm to find the shortest path from one node to another.
		 *
		 * @param   retVector   A pointer to the vector in which the pointers to all the node to be passed by in order to get from the starting node to the destination one shall be inserted.
		 * @param   node1       A pointer to the starting node (it must be a node of this graph, added with {@link #add(T)}).
		 * @param   node2       A pointer to the destination node (it must be a node of this graph, added with {@link #add(T)}).
		 * @return  <code>true</code> if there is a path for getting from the starting node to the destination one or <code>false</code> instead.
		 */
		bool dijkstra(vector<GraphLink<T>*>*, GraphNode<T>*, GraphNode<T>*);

		/**
		 * Applies Dijkstra's algorithm to find the shortest path from one node to another.
		 *
		 * @param   retVector   A pointer to the vector in which the pointers to all the links to be passed by in order to get from the starting node to the destination one shall be inserted.
		 * @param   node1       A pointer to the starting node (it must be a node of this graph, added with {@link #add(T)}).
		 * @param   node2       A pointer to the destination node (it must be a node of this graph, added with {@link #add(T)}).
		 * @return  <code>true</code> if there is a path for getting from the starting node to the destination one or <code>false</code> instead.
		 */
		bool dijkstra(vector<GraphNode<T>*>*, GraphNode<T>*, GraphNode<T>*);

		/**
		 * Find all nodes with a certain value.
		 *
		 * @param   value   The value to be looked for.
		 * @return  retVector   A vector containing pointers to all the found nodes.
		 */
		vector<GraphNode<T>*> getByValue(T);

		/**
		 * Find all nodes with a certain value.
		 *
		 * @param   retVector   A pointer to the vector in which the pointers to the found nodes shall be inserted.
		 * @param   value       The value to be looked for.
		 */
		void getByValue(vector<GraphNode<T>*>*, T);

		/**
		 * Removes a node from this graph and deletes it (if the node is not part of this graph, then it will not be deleted).
		 *
		 * @param   node    A pointer to the node to be removed (it must be a node of this graph, added with {@link #add(T)}).
		 * @return  <code>true</code> if the node was part of the graph and has been successfully removed and deleted, <code>false</code> instead.
		 */
		bool remove(GraphNode<T>*);

	private:
		vector<GraphNode<T>*> nodes;

		static int myDijkstra(vector<GraphNode<T>*>*, GraphNode<T>*, vector<GraphNode<T>*>*, GraphNode<T>*);
};


template<typename T> Graph<T>::Graph() {
}

template<typename T> Graph<T>::~Graph() {
	for(typename vector<GraphNode<T>*>::iterator i = this->nodes.begin(); i != this->nodes.end(); i++) {
		delete(*i);
	};
}

template<typename T> GraphNode<T>* Graph<T>::add(T item) {
	GraphNode<T> *retVal = new GraphNode<T>(item);
	this->nodes.push_back(retVal);

	return retVal;
}

template<typename T> bool Graph<T>::dijkstra(vector<GraphLink<T>*> *retVector, GraphNode<T> *node1, GraphNode<T> *node2) {
	int retVal;
	vector<GraphNode<T>*> *checked = new vector<GraphNode<T>*>();
	vector<GraphNode<T>*> *best = new vector<GraphNode<T>*>();
	if(this->dijkstra(best, node1, node2) == -1) {
		retVal = false;
	} else {
		GraphNode<T> *prev = node1;
		for(typename vector<GraphNode<T>*>::iterator i = best->begin(); i != best->end(); i++) {
			retVector->push_back(prev->getLinkTo(prev = (*i)));
		}
		retVal = true;
	}

	delete(checked);
	delete(best);
	return retVal;
}

template<typename T> bool Graph<T>::dijkstra(vector<GraphNode<T>*> *retVector, GraphNode<T> *node1, GraphNode<T> *node2) {
	bool retVal;
	vector<GraphNode<T>*> *checked = new vector<GraphNode<T>*>();
	retVal = (Graph::myDijkstra(checked, node1, retVector, node2) != -1);
	if(retVal) {
		retVector->insert(retVector->begin(), node1);
	}

	delete(checked);
	return retVal;
}

template<typename T> vector<GraphLink<T>*> Graph<T>::dijkstra(GraphNode<T> *node1, GraphNode<T> *node2) {
	vector<GraphLink<T>*> retVal;
	this->dijkstra(&retVal, node1, node2);

	return retVal;
}

template<typename T> vector<GraphNode<T>*> Graph<T>::getByValue(T value) {
	vector<GraphNode<T>*> retVal;
	this->getByValue(*retVal, value);

	return retVal;
}

template<typename T> void Graph<T>::getByValue(vector<GraphNode<T>*> *retVector, T value) {
	for(typename vector<GraphNode<T>*>::iterator i = this->nodes.begin(); i != this->nodes.end(); i++) {
		if((*i)->value == value) {
			retVector->push_back(*i);
		}
	}
}

template<typename T> bool Graph<T>::remove(GraphNode<T> *node) {
	bool retVal = false;
	typename vector<GraphNode<T>*>::iterator it;
	for(typename vector<GraphNode<T>*>::iterator i = this->nodes.begin(); i != this->nodes.end(); i++) {
		if(*i == node) {
			it = i;
			free(node);
			retVal = true;
		} else {
			(*i)->unconnectTo(node);
		}
	}
	if(retVal) {
		this->nodes.erase(it);
	}

	return retVal;
}

template<typename T> int Graph<T>::myDijkstra(vector<GraphNode<T>*> *checked, GraphNode<T> *current, vector<GraphNode<T>*> *best, GraphNode<T> *destination) {
	int retVal;
	if(current == destination) {
		retVal = 0;
	} else {
		checked->push_back(current);
		vector<GraphNode<T>*> *bestTest = NULL;
		for(typename vector<GraphLink<T>*>::iterator i = current->links.begin(); i != current->links.end(); i++) {
			if(find(checked->begin(), checked->end(), (*i)->next) == checked->end()) {
				vector<GraphNode<T>*> *test = new vector<GraphNode<T>*>();
				test->push_back((*i)->next);
				int currentMetric = Graph::myDijkstra(checked, (*i)->next, test, destination);
				if(currentMetric != -1) {
					currentMetric += (*i)->metric;
				}
				if((currentMetric<retVal || retVal==-1) && currentMetric!=-1) {
					delete(bestTest);
					bestTest = test;
					retVal = currentMetric;
				} else {
					delete(test);
				}
			}
		};
		if(bestTest) {
			best->insert(best->end(), bestTest->begin(), bestTest->end());
			delete(bestTest);
		} else {
			retVal = -1;
		}
		checked->pop_back();
	}

	return retVal;
}

#endif // GRAPH_HPP
