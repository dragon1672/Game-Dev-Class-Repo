#pragma once

#include <ExportHeader.h>
#include <glm/glm.hpp>
#include <Engine\DebugTools\DebugShapeManager.h>
#include <Engine\Pathing\EditorNode.h>

struct EditorNodeConnection {
	EditorNode * to;
	float cost;
	DebugShapeManager::DebugShapeData * renderable;
};