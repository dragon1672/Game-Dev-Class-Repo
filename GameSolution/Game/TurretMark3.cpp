#include "TurretMark3.h"
#include "Bullet.h"
#include <cmath>
float TurretMark3::timeBetweenShots = 0.1;

const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark3Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		17,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 4, 1),	Vector2D( 4,10),
		Vector2D( 5,10),	Vector2D( 3,13),	Vector2D( 1,10),	Vector2D( 2,10),
		Vector2D( 3, 4),	Vector2D( 0, 2),	Vector2D(-3, 4),	Vector2D(-2,10),
		Vector2D(-1,10),	Vector2D(-3,13),	Vector2D(-5,10),	Vector2D(-4,10),
		Vector2D(-4, 1)
);

Shape arrow(RGB(255,0,255),
			Cartesian2Screen * Matrix3D::scale(1),
			7,
			Vector2D(-1,0),
			Vector2D( 1,0),
			Vector2D( 1,4),
			Vector2D( 3,4),
			Vector2D( 0,8),//point
			Vector2D(-3,4),
			Vector2D(-1,4)
);

Shape *TurretMark3::getStyle() {
	return &TurretMark3Style;
}

void TurretMark3::update(float dt, const Vector2D& pos) {
	sinceLastShot+=dt;
	pointToMouse(pos);
	MOUSE.update(dt);
	if(Core::Input::IsPressed( MOUSE.getCheckedElement() )) {
		if(sinceLastShot > timeBetweenShots) { 
			const float distBetweenBullets = 9;
			sinceLastShot = 0;
			Bullet toShoot;
			Matrix3D turretRotation = Matrix3D::rotateToVector(direction.normalized());
			Vector2D offset = turretRotation * Vector2D(distBetweenBullets,0);
			toShoot.pos   = pos+offset+tipOfTurret();
			toShoot.vel   = -100*direction.normalized();
			toShoot.style = &arrow;
			toShoot.rotation=0;
			toShoot.rotationMat = turretRotation;
			shoot(&toShoot);
			offset = turretRotation * Vector2D(-distBetweenBullets,0);
			toShoot.pos   = pos+offset+tipOfTurret();
			shoot(&toShoot);
		}
	}
}