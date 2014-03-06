#pragma warning(disable: 4201)
#pragma warning(push)
#include "NUShapeEditor.h"
#include <ShapeData.h>
#pragma warning(pop)
#include "MyRandom.h"

Neumont::ShapeData NUShapeEditor::fixTeaPotNormals(Neumont::ShapeData& obj) {
	// ???
	return obj;
}
Neumont::ShapeData NUShapeEditor::setModColor(Neumont::ShapeData& obj, int mod) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % mod == 0) {
			float r = Random::randomFloat(0,1);
			float g = Random::randomFloat(0,1);
			float b = Random::randomFloat(0,1);
			//float a = Random::randomFloat(0,1);
			obj.verts[i].color = glm::vec4(r,g,b,1);
		}
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::setColor(glm::vec4& toSet, Neumont::ShapeData& obj, int mod) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % mod == 0) {
			obj.verts[i].color = toSet;
		}
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::initUVData(Neumont::ShapeData& obj) {
	int size = (int)sqrt(obj.numVerts);
	float divisor = (float)size-1;
	for(unsigned int i = 0; i<obj.numVerts; i++)
	{
		int row = (i/size);
		int column = (i%size);
		obj.verts[i].uv = glm::vec2(row/divisor, column/divisor);
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::scale(Neumont::ShapeData& obj, float scale) {
	for(unsigned int i = 0; i<obj.numVerts; i++)
	{
		obj.verts[i].position *= scale;
	}
	return obj;
}