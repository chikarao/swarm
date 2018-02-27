/*
 * Screen.cpp
 *
 *  Created on: Jan 23, 2018
 *      Author: okadachikara
 */
//#include <stdint.h>
#include<iostream>
#include "Screen.h"

using namespace std;

namespace caveofprogramming {

Screen::Screen() :
	m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL),
			m_buffer2(NULL) {

}

bool Screen::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		//		cout << "SDL Init failed" << endl;
		return false;
	}
	m_window = SDL_CreateWindow("Particle Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	// Uint32: 4 bytes
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	// set block of memory with particular value -- makes screen white: 255


	//	buffer[30000] = 0xFFFFFFFF;
	//	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
	//		buffer[i] = 0xFFFF0000; //set all to white same as mem set
	//
	//	}

	return true;

}

//void Screen::testPixel(){
//	m_buffer[30000] = 0xFFFFFFFF;
//			for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
//				m_buffer[i] = 0xFFFF0000; //set all to white same as mem set
//
//			}
//}

//void Screen::colorLoop() {
//	for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
//		for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
//			screen.setPixel(x, y, 128, 0, 255);
//		}
//	}
//}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	static int count = 0;
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return; //only plot on screen if in range
	}
	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	// RGBA Red went through 3 shifts so to get red value

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
	count++;
	//	cout << "inside set pixel: " << count  << endl;
	//	cout << "color: "<< color << endl;
	//	if (count < 100) {
	//		cout << count << "inside set pixel" << endl;
	//	}

}
//
//void Screen::clear() {
//	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
//	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
//get rid of this when blurring
//}

void Screen::boxBlur() {
	//swap the buffers, so pixel info is in m_buffer2 and we are drawing to m_buffer1.
	Uint32 *temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			/*
			 * 000
			 * 010 1 becomes average of colors around it. divide by 9.
			 * 000
			 */
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;
					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY
							>= 0 && currentY < SCREEN_HEIGHT) {
						Uint32 color = m_buffer2[currentY * SCREEN_WIDTH
								+ currentX]; // ???why times it by screen width?? buffer is array of screen width * height
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;

					}
				}
			}
			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;
			setPixel(x, y, red, green, blue);
		}
	}
}

void Screen::update() {
	//using SDL APIs ... this uses only functions underscore avoid collision
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	//copies pixels to buffer; scr_w x 32 is pitch is memory allocated to one row of pixels
	SDL_RenderClear(m_renderer);
	//passing buffer to renderer after clearing it
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
	//presenting renderer on the screen
	//	cout << "ran screen update" << endl;
}

bool Screen::processEvents() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			cout << "process event returning false" << endl;
			return false;
		}

	}
	//	cout << "process event returning true" << endl;
	return true;
}

void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

} //end of namespace

