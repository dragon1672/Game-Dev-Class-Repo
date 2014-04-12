#pragma once

#include <glm/glm.hpp>
#include <GeometryInfo.h>
#include <vector>

struct Node {
	glm::vec3 pos;
	bool isActive;
	std::vector<Node*> connectedNodes;
};