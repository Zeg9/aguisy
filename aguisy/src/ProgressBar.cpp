/*
 * ProgressBar.cpp
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

#include <sstream>
#include "GLStuff.h"
#include "ProgressBar.h"
#include "Event.h"
#include "Style.h"

namespace AGuiSy {
	ProgressBar::ProgressBar(ElementStyle &_style, EventHandler *_handler):
		Element(_style,_handler), percent(50)
	{}
	void ProgressBar::render()
	{
		
		// render
		{
			GLuint t = style.getTexture(state);
			int o = style.getOffset();
			int s = style.getSize();
			float os = (float)o/(float)s;
			// Top left
			drawQuad(x,y,o,o,t,
				0,0,os,os);
			// Top mid
			drawQuad(x+o,y,w-o*2,o,t,
				os,0,1-os*2,os);
			// Top right
			drawQuad(x+w-o,y,o,o,t,
				1.0-os, 0, 1,os);
			// Mid left
			drawQuad(x,y+o,o,h-o*2,t,
				0,os,os,1.0-os);
			// Middle
			drawQuad(x+o,y+o,w-o*2,h-o*2,t,
				os,os,1.0-os,1.0-os);
			// Mid right
			drawQuad(x+w-o,y+o,o,h-o*2,t,
				1.0-os, os, 1, 1.0-os);
			// Bottom left
			drawQuad(x,y+h-o,o,o,t,
				0,1.0-os,os,1.0);
			// Bottom mid
			drawQuad(x+o,y+h-o,w-o*2,o,t,
				os,1.0-os,1-os*2,1.0);
			// Bottom right
			drawQuad(x+w-o,y+h-o,o,o,t,
				1.0-os, 1.0-os, 1,1.0);
		}
		
		// render the bar part
		if (w*percent/100 > style.getOffset())
		{
			GLuint t = style.getTexture(STATE_PRESS);
			int o = style.getOffset();
			int s = style.getSize();
			float os = (float)o/(float)s;
			int wp = w*percent/100;
			// Top left
			drawQuad(x,y,o,o,t,
			0,0,os,os);
			// Top mid
			drawQuad(x+o,y,wp-o*2,o,t,
				os,0,1-os*2,os);
			// Top right
			drawQuad(x+wp-o,y,o,o,t,
				1.0-os, 0, 1,os);
			// Mid left
			drawQuad(x,y+o,o,h-o*2,t,
				0,os,os,1.0-os);
			// Middle
			drawQuad(x+o,y+o,wp-o*2,h-o*2,t,
				os,os,1.0-os,1.0-os);
			// Mid right
			drawQuad(x+wp-o,y+o,o,h-o*2,t,
				1.0-os, os, 1, 1.0-os);
			// Bottom left
			drawQuad(x,y+h-o,o,o,t,
				0,1.0-os,os,1.0);
			// Bottom mid
			drawQuad(x+o,y+h-o,wp-o*2,o,t,
				os,1.0-os,1-os*2,1.0);
			// Bottom right
			drawQuad(x+wp-o,y+h-o,o,o,t,
				1.0-os, 1.0-os, 1,1.0);
		}
		
		// Text render, at middle of element
		{
			std::string t = getRenderText();
			int fs = style.getFontSize();
			vec2 s = style.getFont().textSize(t,fs);
			style.getFont().renderText(t, x+w/2-s.x/2,y+h/2-s.y/2, fs);
		}
	}
	void ProgressBar::event(SDL_Event &e) {} // no event handling
	std::string ProgressBar::getRenderText()
	{
		std::ostringstream oss;
		oss << (int)percent << " %";
		return oss.str();
	}
}
