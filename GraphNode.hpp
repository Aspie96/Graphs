/*
	Copyright (C) 2015 - Code written 100% by Valentino Giudice (valentino.giudice96@gmail.com)

	This work is dual-licensed:
	- under the Do What The Fuck You Want To Public License (version 2): http://www.wtfpl.net/
	- under the CC0 1.0 Universal Public Domain Dedication:              http://creativecommons.org/publicdomain/zero/1.0/

	Enjoy!
	If you want to contact me: valentino.giudice96@gmail.com
*/

#ifndef GRAPHNODE_HPP
#define GRAPHNODE_HPP

#include <stdlib.h>
#include <vector>
#include "Graph.hpp"

using namespace std;

template<typename T> struct GraphLink;
template<typename T> class Graph;

/**
 * This class is used to represent graph nodes. To create an instance of this class {@link Graph#add(T)} shall be used.
 *
 * @param   <T> The type of the content of the node.
 * @see     Graph#add(T)
 * @author  Valentino Giudice
 */
template<typename T> class GraphNode {
	friend class Graph<T>;

	public:
		/**
		 * The content of the node.
		 */
		T value;

		virtual ~GraphNode();

		/**
		 * Creates a link between this node and another one.
		 *
		 * @param   node    A pointer to (it should belong to the same graph).
		 * @param   metric  The metric of the link to be created, also used in the Dijkstra's algorithm (see {@link Graph#dijkstra}).
		 * @return  A pointer to the created link.
		 * @see     GraphLink
		 */
		GraphLink<T> *connectTo(GraphNode<T>*, int);

		/**
		 * Finds the link between this node and another one.
		 *
		 * @param   node A pointer to the linked node (it should belong to the same graph).
		 * @return  A pointer to the found link or <code>NULL</code> if there is no link to the given node.
		 * @see     GraphLink
		 */
		GraphLink<T> *getLinkTo(GraphNode<T>*);

		/**
		 * Unlinks this node to another one and deletes the link itself.
		 *
		 * @param   node A pointer to the linked node (it should belong to the same graph).
		 * @return  <code>true</code> if the two nodes were linked together and the link has been successfully removed or <code>false</code> instead.
		 * @see     GraphLink
		 */
		bool unconnectTo(GraphNode<T>*);

	private:
		vector<GraphLink<T>*> links;

		GraphNode(T);
};


template<typename T> GraphNode<T>::~GraphNode() {
	for(typename vector<GraphLink<T>*>::iterator i = this->links.begin(); i != this->links.end(); i++) {
		free(*i);
	}
}

template<typename T> GraphLink<T>* GraphNode<T>::connectTo(GraphNode<T> *node, int metric) {
	GraphLink<T> *retVal = (GraphLink<T>*)malloc(sizeof(GraphLink<T>));
	retVal->next = node;
	retVal->metric = metric;
	this->links.push_back(retVal);

	return retVal;
}

template<typename T> GraphLink<T>* GraphNode<T>::getLinkTo(GraphNode<T> *node) {
	for(typename vector<GraphLink<T>*>::iterator i = this->links.begin(); i != this->links.end(); i++) {
		if((*i)->next == node) {
			return *i;
		}
	}
	return NULL;
}

template<typename T> bool GraphNode<T>::unconnectTo(GraphNode<T> *node) {
	bool retVal = false;
	for(typename vector<GraphLink<T>*>::iterator i = this->links.begin(); i != this->links.end(); i++) {
		if((*i)->next == node) {
			free(*i);
			this->links.erase(i--);
			retVal = true;
		}
	}

	return retVal;
}

template<typename T> GraphNode<T>::GraphNode(T value) {
	this->value = value;
}

#endif // GRAPHNODE_HPP
