#include <ShapeData.h>

class SingleBufferShape : public Neumont::ShapeData {
public:
	int startOffset;
	uint attribID;


	inline int getDataOffset() {
		return startOffset;
	}
	inline int getIndiceOffset() {
		return startOffset + vertexBufferSize();
	}
	inline int getEndOffset() {
		return startOffset + getTotalBufferSize();
	}
	inline int getTotalBufferSize() {
		return this->vertexBufferSize() + this->indexBufferSize();
	}

	inline void copy(ShapeData& that) {
		this->verts = that.verts;
		this->indices = that.indices;
		this->numVerts = that.numVerts;
		this->numIndices = that.numIndices;
	}

	inline void init(int offset, ShapeData& toCopy) {
		startOffset = offset;
		copy(toCopy);
	}

	void sendToHardware(int bufferID) {
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferSubData(GL_ARRAY_BUFFER,getDataOffset(),vertexBufferSize(),verts);
		glBufferSubData(GL_ARRAY_BUFFER,getIndiceOffset(),indexBufferSize(),indices);

		//glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glGenVertexArrays(1,&attribID);
		glBindVertexArray(attribID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)(getDataOffset() + Neumont::Vertex::POSITION_OFFSET));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)(getDataOffset() + Neumont::Vertex::COLOR_OFFSET));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);

	}

	inline void cleanUp() {
		delete[] verts;		verts = 0;
		delete[] indices;	indices = 0;
	}
};