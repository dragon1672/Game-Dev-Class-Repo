#pragma once

#include <Engine\Physics\Particles\Particle.h>

class ParticleForceGenerator {
public:
	virtual void updateForce(Particle * ctxt) = 0;
};