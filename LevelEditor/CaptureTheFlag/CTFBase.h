#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class CTFBase {
public:
	glm::mat4 * transform;
	glm::vec3 pos;
	float score;
	static const int pointsPerFlag = 739; // dat prime
	CTFBase() {
		transform = nullptr;
		score = 0;
	}
	inline void setPos(glm::vec3& pos) {
		this->pos = pos;
		if(transform != nullptr) (*transform) = glm::translate(pos);
	}
	inline  void setTransform(glm::mat4 * transform) {
		this->transform = transform;
		if(transform != nullptr) (*transform) = glm::translate(pos);
	}
	inline glm::mat4 * getTransform() { return transform; }
	inline glm::vec3 getPos() { return pos; }
	inline void scorePoints() { score += pointsPerFlag; }
	inline int  getscorePoints() { return score; }
};