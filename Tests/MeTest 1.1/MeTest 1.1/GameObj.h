#pragma once

#include "SingleBuffObj.h"
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>

class GameObj {
	SingleBuffObj myStyle;
	glm::vec3 translate;
	float scale;
public:
	void init(SingleBuffObj& myStyle, glm::vec3 translate=glm::vec3(0,0,0), float scale=1) {
		this->myStyle = myStyle;
		this->translate = translate;
		this->scale = scale;
	}
	inline glm::mat4x4 objectToWorld() {
		return glm::translate(translate)
			*= glm::scale(glm::vec3(scale,scale,scale));
	}
	inline SingleBuffObj getMyStyle() {
		return myStyle;
	}
};