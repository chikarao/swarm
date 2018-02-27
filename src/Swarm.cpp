/*
 * Swarm.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: okadachikara
 */

#include "Swarm.h"

namespace caveofprogramming {

Swarm::Swarm(): lastTime(0) {
	// TODO Auto-generated constructor stub
	m_pParticles = new Particle[NPARTICLES]; //??? array of particles?

}

Swarm::~Swarm() {
	// TODO Auto-generated destructor stub
	delete[] m_pParticles;
}

void Swarm::update(int elapsed) {
int interval = elapsed - lastTime;

	for (int i = 0; i < Swarm::NPARTICLES; i++) {
		m_pParticles[i].update(interval);
	}

	lastTime = elapsed;
}

}
