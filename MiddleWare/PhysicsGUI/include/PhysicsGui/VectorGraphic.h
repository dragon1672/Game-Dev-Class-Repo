#ifndef VECTOR_GRAPHIC_H
#define VECTOR_GRAPHIC_H
#include <glm\glm.hpp>
#include <ExportImport.h>

enum DisplayStyle
{
	DS_SQUARE,
	DS_POINT,
	DS_ARROW
};

struct ME_PHYSICS_DLL_SHARED VectorGraphic
{
	VectorGraphic(
		const glm::vec3& position = glm::vec3(),
		const glm::vec3& base = glm::vec3());
	glm::vec3 position;
	glm::vec3 base;
	int r, g, b; // 0 - 255
	float pointSize;
	DisplayStyle displayStyle;
	bool connectToNext;
	bool visible;
};

#endif