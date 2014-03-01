#pragma once

typedef unsigned int uint;

class BinaryVert {
public:
	float POS_X;
	float POS_Y;
	float POS_Z;
	float UV_X;
	float UV_Y;
	float NORM_X;
	float NORM_Y;
	float NORM_Z;
	static const uint POSITION_OFFSET = 0;
	static const uint UV_OFFSET = POSITION_OFFSET + sizeof(float) * 3;
	static const uint NORMAL_OFFSET = UV_OFFSET + sizeof(float) * 2;
	static const uint STRIDE = NORMAL_OFFSET + sizeof(float) * 3;
};