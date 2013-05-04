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
#include <sstream>

std::string tostr(int i)
{
	std::ostringstream oss;
	oss << i;
	return oss.str();
}

bool quit = false;

class MyEventHandler : public AGuiSy::EventHandler
{
	public:
		virtual void onEvent(AGuiSy::Element &element, AGuiSy::Event &event)
		{
			if (event.type == AGuiSy::EVENT_MOUSEUP)
			{
				if (element.getName() == "useless_button")
					std::cout <<
						"Okay, this button isn't useless"
						" -- it shows the hidden entry's text: "
						 << std::endl << '\t'
						 << AGuiSy::getElement("entry2")->getText() << std::endl;
				else if (element.getName() == "startprogress")
				{
					AGuiSy::ProgressBar* bar = (AGuiSy::ProgressBar*)AGuiSy::getElement("progress");
					bar->percent = 0;
				}
				else if (element.getName() == "quit") quit = true;
			}
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
	// Load font
	AGuiSy::Font f(AGuiSy::loadTexture(themePath+"font.png"));
	// Load the layout
	AGuiSy::parseElements(
		"button[pos=10,50;size=128,24;name=useless_button;text=I am a button;]"
		"entry[pos=10,84;size=128,24;name=entry1;text=I am an entry;]"
		"entry[pos=10,118;size=128,24;name=entry2;text=I am hidden !;hidetext=true;]"
		"progressbar[pos=10,200;size=546,24;name=progress;]"
		"button[pos=566,200;size=64,24;name=startprogress;text=Start;]"
		"button[pos=502,446;size=128,24;name=quit;text=Leave me alone;]"
	);
	// Set a nice clear color
	glClearColor(0.1f,0.1f,0.1f,1.0f);
	
	// Main loop
	AGuiSy::ProgressBar* bar = (AGuiSy::ProgressBar*)AGuiSy::getElement("progress");
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			// Pass the event to AGuiSy
			AGuiSy::event(e);
		}
		if (bar->percent < 100)
			bar->percent++;
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
		AGuiSy::render();
		// We're done, swap buffers
		SDL_GL_SwapBuffers();
	}
	// Bye !
	AGuiSy::quit();
	SDL_Quit();
}
