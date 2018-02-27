//============================================================================
// Name        : SDLBasic.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
//#include "Particle.h"
#include "Swarm.h"
#include <stdlib.h>
#include<time.h>

using namespace std;
using namespace caveofprogramming;

int main() {

	srand(time(NULL)); //seed random number generator

	Screen screen; // instantiates screen instance

	if (screen.init() == false) {
		cout << "Error initializing SDL" << endl;
	}

	Swarm swarm; // instantiates swarm instance

	//	int max = 0;

	while (true) {
		//update position
		//draw particles
		//check for messages or events

		int elapsed = SDL_GetTicks();

//		screen.clear();
		swarm.update(elapsed);

		unsigned char green = (1 + sin(elapsed * 0.0005)) * 127;
		unsigned char red = (1 + sin(elapsed * 0.001)) * 127;
		unsigned char blue = (1 + sin(elapsed * 0.0015)) * 127;

		const Particle * const pParticles = swarm.getParticles();
		//const pointer to a class that is const

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];
			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2; //add 1 to make (-1 to +1) to (0 to 2) and * by half screen to cover all of the screen
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2; //so get same circle and move center to middle explosion add 1 to make (-1 to +1) to (0 to 2) and * by half screen to cover all of the screen
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur(); // also gausian blur but uses box blur

		cout << +green << endl;

		//		 for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
		//		 for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
		//		 screen.setPixel(x, y, red, green, blue);
		//
		//		 }
		//		 }


		//this will repeat over and over....
		//screen.colorLoop();
		//		cout << "in while loop" << endl;
		//			screen.setPixel(400, 300, 255, 255, 255);
		//	screen.testPixel();
		screen.update();

		if (screen.processEvents() == false) {
			cout << "breaking" << endl;
			break;
		}
	}
	screen.close();

	return 0;
}
