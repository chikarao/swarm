/*
 * Particle.h
 *
 *  Created on: Jan 24, 2018
 *      Author: okadachikara
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace caveofprogramming {

struct Particle {
	double m_x;
	double m_y;

private:
	double m_speed;// random number between -1 and 1
	double m_direction;

private:
	void init();

public:
	Particle();
	virtual ~Particle();
	void update(int interval);
};

}

#endif /* PARTICLE_H_ */
