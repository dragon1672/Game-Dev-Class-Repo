#include "BasicTurret.h"
#include "Bullet.h"
#include <cmath>
#include "MyRandom.h"
const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape BasicTurretStyle( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		11,
		Vector2D(-3,-2),	Vector2D( 3,-2),	Vector2D( 3, 2),	Vector2D( 1, 2),
		Vector2D( 1, 4),	Vector2D( 3, 4),	Vector2D( 0,13),	Vector2D(-3, 4),
		Vector2D(-1, 4),	Vector2D(-1, 2),	Vector2D(-3, 2)
);

Shape Heart(RGB(255,0,255), Matrix3D::scale(4) * Cartesian2Screen,
	41,
	Vector2D(1     , 0.800000000f),
	Vector2D(0.9f  , 1.107658554f),
	Vector2D(0.8f  , 1.195541753f),
	Vector2D(0.7f  , 1.240642296f),
	Vector2D(0.6f  , 1.259677335f),
	Vector2D(0.5f  , 1.258505748f),
	Vector2D(0.4f  , 1.239176537f),
	Vector2D(0.3f  , 1.201329407f),
	Vector2D(0.2f  , 1.141607594f),
	Vector2D(0.1f  , 1.048972162f),
	Vector2D(0     , 0.800000000f),
	Vector2D(-0.1f , 1.048972162f),
	Vector2D(-0.2f , 1.141607594f),
	Vector2D(-0.3f , 1.201329407f),
	Vector2D(-0.4f , 1.239176537f),
	Vector2D(-0.5f , 1.258505748f),
	Vector2D(-0.6f , 1.259677335f),
	Vector2D(-0.7f , 1.240642296f),
	Vector2D(-0.8f , 1.195541753f),
	Vector2D(-0.9f , 1.107658554f),
	Vector2D(-1    , 0.800000012f),
	Vector2D(-0.9f , 0.410234723f),
	Vector2D(-0.8f , 0.235541753f),
	Vector2D(-0.7f , 0.098013747f),
	Vector2D(-0.6f ,-0.020322665f),
	Vector2D(-0.5f ,-0.127134898f),
	Vector2D(-0.4f ,-0.227247686f),
	Vector2D(-0.3f ,-0.324973315f),
	Vector2D(-0.2f ,-0.426065841f),
	Vector2D(-0.1f ,-0.543007737f),
	Vector2D(0     ,-0.800000000f),
	Vector2D(0.1f  ,-0.543007737f),
	Vector2D(0.2f  ,-0.426065841f),
	Vector2D(0.3f  ,-0.324973315f),
	Vector2D(0.4f  ,-0.227247686f),
	Vector2D(0.5f  ,-0.127134898f),
	Vector2D(0.6f  ,-0.020322665f),
	Vector2D(0.7f  , 0.098013747f),
	Vector2D(0.8f  , 0.235541753f),
	Vector2D(0.9f  , 0.410234723f),
	Vector2D(1     , 0.800000000f)
);

Shape *BasicTurret::getStyle() {
	return &BasicTurretStyle;
}
Vector2D randomVector(float low, float high) {
	return Vector2D(Random::randomFloat(low,high), Random::randomFloat(low,high));
}
void BasicTurret::update(float dt) {
	pointToMouse();
	MOUSE.update(dt);
	if(Core::Input::IsPressed( MOUSE.getCheckedElement() )) {
		if(MOUSE.hasBeenClicked()) { 
			Bullet createdBullet;
			createdBullet.pos   = getParentPos() + tipOfTurret();
			createdBullet.setVel((defaultBulletSpeed*direction) + randomVector(-1,1));
			createdBullet.style = &Heart;
			shoot(&createdBullet);
		}
	}
}