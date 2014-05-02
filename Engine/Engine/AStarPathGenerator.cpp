#include "AStarPathGenerator.h"


namespace AStar {
	void PathGenerator::init(GameNode * nodes, uint numOfGameNodes) {
		if(pathingNodes!=nullptr) {
			delete [] pathingNodes;
		}
		pathingNodes = new Node[numOfGameNodes];
		this->gameNodes = nodes;
		this->numOfGameNodes = numOfGameNodes;
		openList.clear();
	}
	Node * PathGenerator::convertToNode(GameNode * gNode) {
		uint id = gNode - gameNodes;
		glm::vec3 diff = end->pos - gNode->pos;
		pathingNodes[id].init(glm::length(diff),gNode);
		return &(pathingNodes[id]);
	}

	//inits Node data and returns if valid Node
	void PathGenerator::processNode(Node * toProcess, Node * parentNode, float connectionCost) {
		if(toProcess->node == start) return;
		if(toProcess->parent != nullptr)
		{
			Node possibleReplacement = toProcess->clone();
			possibleReplacement.setParent(parentNode,connectionCost);


			if(possibleReplacement.isCheaper(toProcess)) {
				toProcess->setParent(parentNode,connectionCost); // also calculates
			} else {
				return ;// not optimal to recalculate
			}
		} else {
			toProcess->setParent(parentNode,connectionCost); // also calcuates
		}
		openList.push_back(toProcess);
	}
	/*
	PathNode* nodeToUpdate = &pathNodes[connectionIndex];

	//find the cost by seeing if the node has been processed or not
	if(nodeToUpdate->proccesed())
	{
		PathNode temp = *nodeToUpdate;
		temp.parrent = currentNode;
		temp.costSoFar = currentNode->costSoFar + concs->cost;
		if(nodeToUpdate->totalEstimatedCost() > temp.totalEstimatedCost())
		{
			nodeToUpdate->costSoFar = temp.costSoFar;
			nodeToUpdate->parrent = temp.parrent;
			//add connection to open list
			openList.push(&pathNodes[connectionIndex]);
		}
		//node hasn't changed so don't put it on openList ( no else)
	}
	else
	{
		nodeToUpdate->costSoFar = currentNode->costSoFar + concs->cost;
		nodeToUpdate->parrent = currentNode;
		//add connection to open list
		openList.push(&pathNodes[connectionIndex]);
	}
}
	//*/

	Node * PathGenerator::popCheapestNode() {
		int cheapestId = -1;
		for (uint i = 0; i < openList.size(); i++)
		{
			if(cheapestId<0 || openList[cheapestId]->estimatedTotalCost > openList[i]->estimatedTotalCost) {
				cheapestId = i;
			}
		}

		Node * ret = openList[cheapestId];
		openList.erase(openList.begin() + cheapestId);

		return ret;
	}
	void PathGenerator::updateValues() {
		for (uint i = 0; i < numOfGameNodes; i++)
		{
			convertToNode(&gameNodes[i]);
		}
	}
	GameNode * PathGenerator::findClosestNode(glm::vec3& pos) {
		GameNode * ret = nullptr;
		float currentDist;
		for (int i = 0; i < numOfGameNodes; i++)
		{
			float testingDistance = glm::length(gameNodes[i].pos - pos);
			if(ret == nullptr || testingDistance < currentDist)  {
				currentDist = testingDistance;
				ret = &gameNodes[i];
			}
		}
		return ret;
	}
			
	Path PathGenerator::genPath(Node * endSeed) {
		Path ret;
		ret.validPath = true;
		Node * currentNode = endSeed;
		do {
			ret.positions.push_back(currentNode->node->pos);
			currentNode = currentNode->parent;
			if(currentNode==nullptr) break;
		} while(currentNode->parent != nullptr);
		return ret;
	}
	//generates and returns path
	Path PathGenerator::getPath(GameNode * start, GameNode * end) {
		this->start = start;
		this->end = end;
		updateValues();
		//init open list
		openList.clear();
		openList.push_back(convertToNode(start));

		Node * endNode = &pathingNodes[numOfGameNodes-1];

		while(openList.size() > 0) {
			Node * processingParent = popCheapestNode(); // removes nodes for open
				
			//if end is found
			if(processingParent->node == end || endNode->parent != nullptr) {
				return genPath(processingParent);
			}
			//process connections
			for (int i = 0; i < processingParent->node->numOfConnections; i++)
			{
				uint nodeID = processingParent->node->connections[i].to - gameNodes;
				processNode(&pathingNodes[nodeID],processingParent, processingParent->node->connections[i].cost);
				Node * temp = &pathingNodes[nodeID];
			}
		}
		//invalid path
		Path ret;
		ret.validPath = false;
		return ret;
	}
	Path PathGenerator::getPath(glm::vec3 start, glm::vec3 end) {
		Path ret;
		if(start != end) {
			GameNode * startNode = findClosestNode(start);
			GameNode * endNode   = findClosestNode(end);
			ret = getPath(startNode,endNode);
			ret.positions.insert(ret.positions.begin(),end);
			ret.positions.push_back(start);
		} else {
			ret.validPath = false;
		}
		return ret;
	}
}