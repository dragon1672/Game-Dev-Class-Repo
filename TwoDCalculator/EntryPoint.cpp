#include "RenderUI.h"

int main(int argc, char* argv[])
{
	RenderUI renderUI;

	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}