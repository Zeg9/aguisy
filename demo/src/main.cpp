/*
 * main.cpp
 * This file is part of AGuiSy
 *
 * Copyright (C) 2013 - Zeg9
 *
 * AGuiSy is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * AGuiSy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with AGuiSy. If not, see <http://www.gnu.org/licenses/>.
 */

#include <AGuiSy/AGuiSy.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

GLuint loadTexture(const char * filename);
SDL_Surface * flipSurface(SDL_Surface * surface);

int main(int argc,char**argv)
{
	// Init SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(640,480,32,SDL_OPENGL);
	// Init GLEW
	glewInit();
	// Init AGuiSy
	AGuiSy::init();
	// Load font
	AGuiSy::Font f(AGuiSy::loadTexture("../data/font.png"));
	// Load button style
	AGuiSy::ElementStyle buttonStyle("../data/simpledark/button","../data/font.png");
	// Create an element
	AGuiSy::Element el(buttonStyle);
	el.setPos(10,50);
	el.setSize(128,24);
	el.setText("I am a button");
	// Set a nice clear color
	glClearColor(0.1f,0.1f,0.1f,1.0f);
	
	// Main loop
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				// You can enable this code to see the element's resizability
				/*Uint8 state = SDL_GetMouseState(0,0);
				if(state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					AGuiSy::vec2 s = el.getSize();
					el.setPos(e.motion.x-s.x/2,e.motion.y-s.y/2);
				} else if (state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
					AGuiSy::vec2 p = el.getPos();
					el.setSize(e.motion.x-p.x,e.motion.y-p.y);
				}*/
			}
			// Pass the event to the element
			el.event(e);
		}
		// Clear the screen, then render
		glClear(GL_COLOR_BUFFER_BIT);
		// Little background text
		f.renderText("Welcome to AGuiSy !", 10, 10, 24);
		// Render our nice element
		el.render();
		// We're done, swap buffers
		SDL_GL_SwapBuffers();
	}
	// Bye !
	SDL_Quit();
}



