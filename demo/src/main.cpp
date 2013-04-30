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

class MyEventHandler : public AGuiSy::EventHandler
{
	public:
		virtual void onEvent(AGuiSy::Element &element, AGuiSy::Event &event)
		{
			std::cout << "event !!" << event.type << std::endl;
		}
};

int main(int argc,char**argv)
{
	// Init SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableUNICODE(1);
	SDL_WM_SetCaption("AGuiSy demo",0);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_SetVideoMode(640,480,32,SDL_OPENGL);
	// Init GLEW
	glewInit();
	// Init AGuiSy
	AGuiSy::init();
	// Load font
	AGuiSy::Font f(AGuiSy::loadTexture("../data/font.png"));
	// Load styles
	AGuiSy::ElementStyle buttonStyle("../data/simpledark/button","../data/font.png");
	AGuiSy::ElementStyle entryStyle("../data/simpledark/entry","../data/font.png");
	// Make an instance of my event handler
	MyEventHandler handler;
	// Create an element
	AGuiSy::Button button(buttonStyle,handler);
	button.setPos(10,50);
	button.setSize(128,24);
	button.setText("I am a button");
	AGuiSy::Entry entry(entryStyle,handler);
	entry.setPos(10,50+24+10);
	entry.setSize(128,24);
	entry.setText("");
	AGuiSy::Entry entry2(entryStyle,handler);
	entry2.setPos(10,50+24*2+10*2);
	entry2.setSize(128,24);
	entry2.setHideText(true);
	entry2.setText("");
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
			button.event(e);
			entry.event(e);
			entry2.event(e);
			// TODO (in the library): AGuiSy::event(e) and AGuiSy::render()
		}
		// Clear the screen, then render
		glClear(GL_COLOR_BUFFER_BIT);
		// Little background text
		f.renderText("Welcome to AGuiSy !", 10, 10, 24);
		f.renderText(
			"AGuiSy is a work-in-progress.\n"
			"There is still a lot to do.\n"
			, 10, 50+24*3+10*3, 16);
		// Label elements
		f.renderText("<- A simple button. Try to click it, but IIRC it is useless", 128+10, 50+4, 16);
		f.renderText("<- A text entry, click it to focus and write text in it.", 128+10, 50+24+10+4, 16);
		f.renderText("<- An entry with hidden text, good for passwords", 128+10, 50+24*2+10*2+4, 16);
		// Render our nice elements
		button.render();
		entry.render();
		entry2.render();
		// We're done, swap buffers
		SDL_GL_SwapBuffers();
	}
	// Bye !
	SDL_Quit();
}



