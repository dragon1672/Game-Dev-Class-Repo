#include "ScoreManager.h"
#include "TeamInfo.h"
//for draw
#include "Font.h"
#include "FontRender.h"
#include "MyGraphics.h"
#include "TextFormatting.h"
#include <sstream>

void ScoreManager::LivingEntityDeath(LivingGameEntity * thatDied) {
	if(TeamInfo::ENEMY_TEAM == thatDied->getTeam()) {
		addPoints((int)(thatDied->getMaxHeath()/4));
	}
}
int  ScoreManager::getTotalPoints() {
	return totalPoints;
}
void ScoreManager::addPoints(int amount) {
	ASSERT(amount>0,"trying to pass a neg amount of points to add");
	totalPoints += amount;
}
void ScoreManager::spendPoints(int amount) {
	ASSERT(amount>0,"trying to pass a neg amount of points to spend");
	totalPoints -= amount;
};
void ScoreManager::resetPoints() {
	totalPoints = 0;
}
void ScoreManager::draw(MyGraphics& graphics, Vector2D& pos, int size, Core::RGB color) {
	TextFormatting format;
	format.init(size,1,color,size);
	std::stringstream ss;
	ss << totalPoints;
	FontRender::draw(graphics,pos,&Font::defaultFont,&format,ss.str().c_str());
}