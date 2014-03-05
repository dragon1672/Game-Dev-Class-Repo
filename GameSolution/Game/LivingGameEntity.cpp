#include "LivingGameEntity.h"
#include "TeamInfo.h"

void LivingGameEntity::checkLifeCap() {
	life = (life>maxLife)? maxLife : life;
	life = (life<0)? 0 : life;
}
void  LivingGameEntity::initFullHealth(float amount) {
	ASSERT(amount>0,"Initilizing health below 0");
	maxLife = amount;
	life = maxLife;
}
void  LivingGameEntity::addHP(float amount) {
	ASSERT(amount>0,"Adding negitive health 0");
	life+=amount;
	checkLifeCap();
}
void  LivingGameEntity::removeHP(float amount) {
	ASSERT(amount>0,"trying to removing negitive 0");
	life-=amount;
	checkLifeCap();
}
float LivingGameEntity::getHealthPercent() {
	return life/maxLife;
}
float LivingGameEntity::getHealth() { return life; }
float LivingGameEntity::getMaxHeath() { return maxLife; }
void  LivingGameEntity::setMaxHealth(float amount) {
	ASSERT(amount>0,"Max health must be above 0");
	maxLife = amount;
	checkLifeCap();
}
bool  LivingGameEntity::isAlive() {
	return (life > 0);
}
void  LivingGameEntity::collisionDamage(LivingGameEntity * collidedWith) {
	if(collidedWith->getTeam()==TeamInfo::FRIENLY_TEAM && getTeam()==TeamInfo::ENEMY_TEAM)   removeHP(3);
	if(collidedWith->getTeam()==TeamInfo::ENEMY_TEAM   && getTeam()==TeamInfo::FRIENLY_TEAM) removeHP(3);
}