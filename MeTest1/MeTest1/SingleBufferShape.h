#include <ShapeData.h>

class SingleBufferShape : public Neumont::ShapeData {
public:
	int startOffset;
	uint attribID;


	inline int getDataOffset();
	inline int getIndiceOffset();
	inline int getEndOffset();
	inline int getTotalBufferSize();

	inline void copy(ShapeData& that);

	inline void init(int offset, ShapeData& toCopy);

	void sendToHardware(int bufferID);

	inline void cleanUp();
};