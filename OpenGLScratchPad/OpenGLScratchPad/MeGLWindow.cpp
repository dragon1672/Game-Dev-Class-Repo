#include <gl/glew.h>
#include "MeGLWindow.h"
#include <glm/glm.hpp>

typedef glm::vec2 Vector2D;
typedef glm::vec3 Vector3D;

void MeGLWindow::initializeGL() {
	glewInit();

	Vector3D verts[] = {
		Vector3D(+0.0f, +0.8f, +0.0f),
		Vector3D(+1.0f, +0.0f, +0.0f),

		Vector3D(-0.8f, -0.8f, +0.0f),
		Vector3D(+0.0f, +1.0f, +0.0f),

		Vector3D(+0.8f, -0.8f, +0.0f),
		Vector3D(+0.0f, +0.0f, +1.0f),

	};
	GLuint bufferID;
	glGenBuffers(1,&bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(Vector3D),0);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2*sizeof(Vector3D), (void *)(sizeof(Vector3D)));
}
void MeGLWindow::paintGL() {
	glDrawArrays(GL_TRIANGLES,0,3);
}