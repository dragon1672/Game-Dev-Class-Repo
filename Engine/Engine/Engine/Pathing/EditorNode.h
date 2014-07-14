#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include <vector>
#include <ExportHeader.h>
#include <Engine\DebugTools\DebugShapeManager.h>
#include <Engine\Tools\Ray.h>
#include <Engine\unsigned.h>

struct EditorNodeConnection;

struct ENGINE_SHARED EditorNode {
	static const int radius=1;
	glm::vec3 pos;
	std::vector<EditorNodeConnection *> connections;


	DebugShapeManager::DebugShapeData * rednerable;
	int  shutdown(); // returns numberOfConnections deleted
	int  removeNode(EditorNode * idtoRemove); // returns numberOfConnections deleted
	void activateConnections(glm::vec4& color);
	void activateConnection(glm::vec3& nodePos, glm::vec4& color);
	bool validConnection(EditorNode * toConnect);
	int getConnectionId(EditorNode * toConnect);
	void deleteConnection(uint id);
	void setConnectionState(bool state);
	
	bool doesRayHit(Ray& ray); //cheap
	static bool doesRayHit(Ray& ray, glm::vec3 orgin, float radius);
	bool tryIntersectionVector(Ray& ray, glm::vec3& ret); //uses sqrt
};