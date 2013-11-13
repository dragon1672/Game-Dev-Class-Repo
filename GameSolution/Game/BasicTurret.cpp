#include "BasicTurret.h"
#include "Bullet.h"
#include <cmath>
const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape BasicTurretStyle( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		11,
		Vector2D(-3,-2),	Vector2D( 3,-2),	Vector2D( 3, 2),	Vector2D( 1, 2),
		Vector2D( 1, 4),	Vector2D( 3, 4),	Vector2D( 0,13),	Vector2D(-3, 4),
		Vector2D(-1, 4),	Vector2D(-1, 2),	Vector2D(-3, 2)
);

const float bulletScale = 4;
Shape defaultBasicBulletStyle(RGB(255,0,255),
	Cartesian2Screen * Matrix3D::scale(bulletScale), 
	5,
	Vector2D(   .7f, -1.0f ),
	Vector2D(  0.0f,  1.0f ),
	Vector2D(  -.6f, -1.0f ),
	Vector2D(  1.0f,   .25f),
	Vector2D( -1.0f,   .25f) 
);

Shape *BasicTurret::getStyle() {
	return &BasicTurretStyle;
}

void BasicTurret::update(float dt, const Vector2D& pos) {
	pointToMouse(pos);
	MOUSE.update(dt);
	if(Core::Input::IsPressed( MOUSE.getCheckedElement() )) {
		if(MOUSE.hasBeenClicked()) { 
			Bullet toShoot;
			toShoot.pos   = pos;
			toShoot.vel   = -100*direction.normalized();
			toShoot.style = &defaultBasicBulletStyle;
			shoot(&toShoot);
		}
	}
}