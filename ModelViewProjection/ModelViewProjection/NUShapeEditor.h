#pragma once

#include <ShapeData.h>

class NUShapeEditor {
public:
	static Neumont::ShapeData fixTeaPotNormals(Neumont::ShapeData& obj);
	static Neumont::ShapeData setModColor(Neumont::ShapeData& obj, int mod=1);
	static Neumont::ShapeData setColor(glm::vec4& toSet, Neumont::ShapeData& obj, int mod = 1);
	static Neumont::ShapeData initUVData(Neumont::ShapeData& obj);
	static Neumont::ShapeData scale(Neumont::ShapeData& obj, float scale);
};