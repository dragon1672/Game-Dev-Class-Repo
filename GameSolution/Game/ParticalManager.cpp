#include "ParticalManager.h"
#include "AutoProfileManager.h"

void ParticalManager::newEffect(int size, ParticalEffect *effect) {
	for(int i=0;i<MAX_PARTICALS;i++) {
		if(particals[i].lifetime<=0 && size>0) {
			size--;
			particals[i].myEffect = effect;
			effect->initPartical(&particals[i]);
		}
	}
	if(size>0) 1==1;//not enough memory for all effects
}
void ParticalManager::update(float dt) {
	for(int i=0;i<MAX_PARTICALS;i++) {
		if(particals[i].lifetime>0) {
			PROFILE("Single Partical Update");
			particals[i].update(dt);
			END_PROFILE;
		}
	}
}
void ParticalManager::draw(Core::Graphics graphics) {
	for(int i=0;i<MAX_PARTICALS;i++) {
		if(particals[i].lifetime>0) {
			PROFILE("Single Partical Draw");
			particals[i].draw(graphics);
			END_PROFILE;
		}
	}
}