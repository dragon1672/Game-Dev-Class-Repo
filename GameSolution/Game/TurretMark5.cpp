#include "TurretMark5.h"
#include "Bullet.h"
#include <cmath>
float TurretMark5::timeBetweenShots = 1/50;
const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark5Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		11,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 6, 2),	Vector2D( 6, 6),
		Vector2D( 1,13),	Vector2D( 3, 5),	Vector2D( 0, 2),	Vector2D(-3, 5),
		Vector2D(-1,13),	Vector2D(-6, 6),	Vector2D(-6, 2)
);
Shape *TurretMark5::getStyle() {
	return &TurretMark5Style;
}

void TurretMark5::update(float dt, const Vector2D& pos) {
	sinceLastShot+=dt;
	pointToMouse(pos);
	MOUSE.update(dt);
	if(Core::Input::IsPressed( MOUSE.getCheckedElement() )) {
		if(sinceLastShot > timeBetweenShots) { 
			sinceLastShot = 0;
			Bullet toShoot;
			toShoot.pos   = pos+tipOfTurret();
			toShoot.vel   = -100*direction.normalized();
			toShoot.style = &defaultBulletStyle;
			shoot(&toShoot);
		}
	}
}