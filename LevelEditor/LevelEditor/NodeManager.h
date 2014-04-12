#pragma once

#include <vector>
#include "Node.h"
#include <map>

typedef unsigned int uint;

class NodeManager {
	Node nodes[100];
	uint numOfNodes;
	Node * currentSelectedNode;
};