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

AGuiSy::Element *entry2(0);

class MyEventHandler : public AGuiSy::EventHandler
{
	public:
		virtual void onEvent(AGuiSy::Element &element, AGuiSy::Event &event)
		{
			//std::cout << "event: " << event.type << " on element " << element.getName() << std::endl;
			if (element.getName() == "button" && event.type == AGuiSy::EVENT_MOUSEDOWN)
				std::cout <<
					"Okay, this button isn't useless -- it show the hidden entry's text: "
					 << std::endl << '\t' << entry2->getText() << std::endl;
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
	std::string themePath = "../data/themes/simpledark/";
	AGuiSy::init(themePath, new MyEventHandler());
	// Load styles
	AGuiSy::Font f(AGuiSy::loadTexture(themePath+"font.png"));
	AGuiSy::ElementStyle buttonStyle(themePath+"button",themePath+"font.png");
	AGuiSy::ElementStyle entryStyle(themePath+"entry",themePath+"font.png");
	// Make an instance of my event handler
	// Create an element
	// TODO implement below:
	/*AGuiSy::loadElements(
		"button[pos=10,50;size=128,24;name=button;text=I am a button]"
		"entry[pos=10,84;size=128,24;name=entry1]"
		"entry[pos=10,118;size=128,24;name=entry2;hide=true]");*/
	AGuiSy::Element *button = AGuiSy::parseElement(
		"button[pos=10,50;size=128,24;name=button;text=I am a button;]");
	AGuiSy::Element *entry = AGuiSy::parseElement(
		"entry[pos=10,84;size=128,24;name=entry;text=I am an entry;]");
	entry2 = AGuiSy::parseElement(
		"entry[pos=10,118;size=128,24;name=entry2;text=I am hidden !;hidetext=true;]");
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
			button->event(e);
			entry->event(e);
			entry2->event(e);
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
		button->render();
		entry->render();
		entry2->render();
		// We're done, swap buffers
		SDL_GL_SwapBuffers();
	}
	// Bye !
	AGuiSy::quit();
	SDL_Quit();
}



