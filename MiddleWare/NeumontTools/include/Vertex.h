#ifndef NEUMONT_VERTEX_H
#define NEUMONT_VERTEX_H
#include "TypeDefs.h"
#include "ExportImportHeader.h"
#include "glm\glm.hpp"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

template struct DLL_SHARED glm::detail::tvec2<float>;
template struct DLL_SHARED glm::detail::tvec3<float>;
template struct DLL_SHARED glm::detail::tvec4<float>;

namespace Neumont
{
	struct DLL_SHARED Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;
		static uint POSITION_OFFSET;
		static uint COLOR_OFFSET;
		static uint NORMAL_OFFSET;
		static uint UV_OFFSET;
		static uint STRIDE;
	};
}

#endif