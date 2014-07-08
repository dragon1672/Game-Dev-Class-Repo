#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class ShaderProgram;

class MatrixInfo {
private:
	glm::mat4 transform;
	glm::mat4 preTransform;
	glm::mat4 postTransform;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	inline void updateMatrix() {
		transform = (enablePreTransform ? preTransform : glm::mat4())
			* glm::translate(position)
			* glm::rotate(rotation.x,glm::vec3(1,0,0))
			* glm::rotate(rotation.y,glm::vec3(0,1,0))
			* glm::rotate(rotation.z,glm::vec3(0,0,1))
			* glm::scale(scale)
			* (enablePostTransform ? postTransform : glm::mat4());
	}
public:
	bool enablePreTransform;
	bool enablePostTransform;
	inline void setPos(glm::vec3&	 toSet) { position = toSet; updateMatrix(); }
	inline void setRot(glm::vec3&	 toSet) { rotation = toSet; updateMatrix(); }
	inline void setScale(glm::vec3& toSet) { scale    = toSet; updateMatrix(); }
	inline void setPreTrans(glm::mat4& toSet)  { preTransform  = toSet; updateMatrix(); }
	inline void setPostTrans(glm::mat4& toSet) { postTransform = toSet; updateMatrix(); }

	inline glm::vec3& getPos() { return position; }
	inline glm::vec3& getRot() { return rotation; }
	inline glm::vec3& getScale() { return scale;  }
	inline glm::mat4& getPreTransform()  { return preTransform;  }
	inline glm::mat4& getPostTransform() { return postTransform; }
	inline glm::mat4& getTransform()     { return transform;     } // save this on in the Shader
};