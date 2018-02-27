/*
 * Particle.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: okadachikara
 */

#include "Particle.h"
#include <math.h>
#include <stdlib.h>

namespace caveofprogramming {

Particle::Particle() :
	m_x(0), m_y(0) {

	// TODO Auto-generated constructor stub
	//	m_x = (2.0 * (double) rand()) / RAND_MAX - 1; // random num between -1 and 1
	//	m_y = (2.0 * (double) rand()) / RAND_MAX - 1; // random num between -1 and 1

	//	m_xSpeed = 0.01 * (((2.0 * rand()) / RAND_MAX) - 1);// random number between -1 and 1
	//	m_ySpeed = 0.01 * (((2.0 * rand()) / RAND_MAX) - 1);
	init();

}

void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = (2 * M_PI * rand()) / RAND_MAX; // choosing angle
	m_speed = (0.04 * rand()) / RAND_MAX;

	m_speed *= m_speed; //exaggerates larger numbers
}

void Particle::update(int interval) {

	m_direction += interval * 0.0002;

	double xSpeed = m_speed * cos(m_direction);
	double ySpeed = m_speed * sin(m_direction);

	m_x += xSpeed * interval;
	m_y += ySpeed * interval;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}

	if(rand() < RAND_MAX/100) {
		init();
	}
	//
	//	if(m_x <= -1.0 || m_x >= 1.0) {
	//		m_xSpeed = -m_xSpeed;
	//	}
	//	if(m_y <= -1.0 || m_y >= 1.0) {
	//			m_ySpeed = -m_ySpeed;
	//		}

}
Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

}
