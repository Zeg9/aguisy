/*
 * Style.cpp
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

#include "Style.h"
#include "SDLStuff.h"

namespace AGuiSy {
	ElementStyle::ElementStyle(std::string path, std::string fontpath):
		normal(loadTexture(path+"_normal.png")),
		hover(loadTexture(path+"_hover.png")),
		press(loadTexture(path+"_press.png")),
		inactive(loadTexture(path+"_inactive.png")),
		font(loadTexture(fontpath))
	{}
	ElementStyle::~ElementStyle() {}
	GLuint ElementStyle::getTexture(State s)
	{
		switch (s)
		{
			case STATE_NORMAL:
				return normal;
				break;
			case STATE_HOVER:
				return hover;
				break;
			case STATE_PRESS:
				return press;
				break;
			case STATE_INACTIVE:
				return inactive;
				break;
			default: // shouldn't happen, but...
				return inactive;
				break;
		}
	}
	int ElementStyle::getOffset()
	{
		return 4; //FIXME please don't hard-code me !!
	}
	int ElementStyle::getSize()
	{
		return 16; // FIXME same as above !!
	}
	Font &ElementStyle::getFont()
	{
		return font;
	}
	int ElementStyle::getFontSize()
	{
		return 16; // FIXME, hard coded value -- again
	}
}
