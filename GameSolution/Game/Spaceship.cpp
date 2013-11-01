#include "SpaceShip.h"
#include "GameSpace.h"

const float Spaceship::brakePower = 200;
const Vector2D accX(100, 0);
const Vector2D accY(0, 100);

float Spaceship::TURRET_LENGTH = 30;
Core::RGB Spaceship::shipColor = RGB(255,255,0);
Shape Spaceship::thisShape( shipColor,
							7,
							Vector2D(10,12),
							Vector2D(12, 0 ),
							Vector2D( 8,  8 ),
							Vector2D( 0, -20),//tip
							Vector2D(-8,  8 ),
							Vector2D(-12, 0 ),
							Vector2D(-10, 12)
							);
void Spaceship::addAcc(Vector2D toAdd, float scalar) {
	vel = vel+(scalar*toAdd);
}
void Spaceship::brake(float scalar) {
	float newX = 0;
	float brakePower = scalar*(this->brakePower);
	float current = vel.getX();
	if(current!=0) {
		float toSub = (current>0)? brakePower : -brakePower ;
		newX = (abs(toSub)<abs(current))? current-toSub: 0;
	}
	float newY = 0;
	current = vel.getY();
	if(current!=0) {
		float toSub = (current>0)? brakePower : -brakePower ;
		newY = (abs(toSub)<abs(current))? current-toSub: 0;
	}
	vel = Vector2D(newX,newY);
}
float Spaceship::getMinX() { return pos.getX()+thisShape.getMinX(); }
float Spaceship::getMinY() { return pos.getY()+thisShape.getMinY(); }
float Spaceship::getMaxX() { return pos.getX()+thisShape.getMaxX(); }
float Spaceship::getMaxY() { return pos.getY()+thisShape.getMaxY(); }
void Spaceship::manageAcc(float dt) {
	if(Core::Input::IsPressed( Core::Input::KEY_UP        )) addAcc(-accY,dt);
	if(Core::Input::IsPressed( Core::Input::KEY_DOWN      )) addAcc( accY,dt);
	if(Core::Input::IsPressed( Core::Input::KEY_LEFT      )) addAcc(-accX,dt);
	if(Core::Input::IsPressed( Core::Input::KEY_RIGHT     )) addAcc( accX,dt);
	if(Core::Input::IsPressed( Core::Input::BUTTON_SHIFT  )) brake (dt);
}
void Spaceship::move(float dt) {
	pos = pos+(dt*vel);
	if(Core::Input::IsPressed( Core::Input::LETTER_Z      )) warp();
	else if(Core::Input::IsPressed( Core::Input::LETTER_X      )) bounce();
	else collide();
}
float Spaceship::mouseDistanceFromTurretLine() {
	float mouseX = (float)Core::Input::GetMouseX();
	float mouseY = (float)Core::Input::GetMouseY();
	Vector2D mouse(mouseX,mouseY);
	Vector2D temp = mouse-pos;
	Vector2D anotherTemp = turret.perpCW().normalized();
	float tempFloat = temp.dot(anotherTemp);
	return tempFloat;
}
bool Spaceship::mouseWithinTurretRange() {
	float mouseX = (float)Core::Input::GetMouseX();
	float mouseY = (float)Core::Input::GetMouseY();
	Vector2D mouse(mouseX,mouseY);
	Vector2D testOne = pos-mouse;
	Vector2D testTwo = (pos+ turret) - mouse;
	return (testOne.dot(testTwo) < 0);
	//return ((mouse-pos).lengthSquared()<turret.lengthSquared());//is within turrent length from shipPos
}
void Spaceship::updateTurret() {
	if(Core::Input::IsPressed( Core::Input::BUTTON_LEFT) && mouseWithinTurretRange()) {
		int error=5;
		float mouseDist = mouseDistanceFromTurretLine();
		if(-error<mouseDist && mouseDist<error) {
			float mouseX = (float)Core::Input::GetMouseX();
			float mouseY = (float)Core::Input::GetMouseY();
			Vector2D mouse(mouseX,mouseY);
			turret = TURRET_LENGTH*((mouse-pos).normalized());
			if(turret.isZero()) resetTurret();
		}
	}
}
void Spaceship::update(float dt) {
	manageAcc(dt);
	move(dt);
	updateTurret();
}
void Spaceship::draw(Core::Graphics graphics) {
	this->thisShape.draw(graphics,pos);
	graphics.DrawLine(pos.getX(), pos.getY(), (pos+turret).getX(), (pos+turret).getY());
}
void Spaceship::resetTurret() {
	turret = Vector2D(0,TURRET_LENGTH);
}
void Spaceship::init(float x, float y, GameSpace *space/*, GameWorld world*/) {
	pos = Vector2D(x,y);
	this->space = space;
	resetTurret();
}
//collide
void Spaceship::warp() {
	if(pos.getX() < (*space).getMin().getX()) pos = Vector2D( (*space).getMax().getX(), pos.getY());
	if(pos.getY() < (*space).getMin().getY()) pos = Vector2D( pos.getX(),               (*space).getMax().getY() );
	if(pos.getX() > (*space).getMax().getX()) pos = Vector2D( (*space).getMin().getX(), pos.getY());
	if(pos.getY() > (*space).getMax().getY()) pos = Vector2D( pos.getX(),               (*space).getMin().getY() );
}
void Spaceship::bounce() {
	if(pos.getX() < (*space).getMin().getX() || pos.getX() > (*space).getMax().getX()) vel = Vector2D(-vel.getX(), vel.getY());
	if(pos.getY() < (*space).getMin().getY() || pos.getY() > (*space).getMax().getY()) vel = Vector2D( vel.getX(),-vel.getY());
}
void Spaceship::collide() {
	vel = space->collideVector(pos,vel);
}