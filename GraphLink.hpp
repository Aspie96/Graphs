/*
	Copyright (C) 2015 - Code written 100% by Valentino Giudice (valentino.giudice96@gmail.com)

	This work is dual-licensed:
	- under the Do What The Fuck You Want To Public License (version 2): http://www.wtfpl.net/
	- under the CC0 1.0 Universal Public Domain Dedication:              http://creativecommons.org/publicdomain/zero/1.0/

	Enjoy!
	If you want to contact me: valentino.giudice96@gmail.com
*/

#ifndef GRAPHLINK_H
#define GRAPHLINK_H

#include "GraphNode.hpp"

template<typename T> class GraphNode;

/**
 * This structure is used to represent links between class nodes.
 *
 * @param   <T> The type of the content of the linked nodes node.
 * @see     GraphNode
 * @author  Valentino Giudice
 */
template<typename T> struct GraphLink {
	/**
	 * The metric of this node, used in Dijkstra's algorithm.
	 *
	 * @see Graph#dijkstra
	 */
	int metric;

	/**
	 * A pointer to the node the node containing this link is linked to.
	 */
	GraphNode<T> *next;
};

#endif // GRAPHLINK_H
