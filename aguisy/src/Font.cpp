/*
 * Font.cpp
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


#include "Font.h"
#include "GLStuff.h"

namespace AGuiSy {
	Font::Font(GLuint textureid)
	 : texture(textureid)
	{}
	
	Font::~Font()
	{}
	
	void Font::renderChar(char c, int x, int y, int size)
	{
		float uvx = (c%16)/16.0;
		float uvy = (c/16)/16.0;
		drawQuad(x,y,size,size,texture,
			uvx, uvy, uvx+1.0/16.0,uvy+1.0/16.0);
	}
	
	void Font::renderText(std::string text, int x, int y, int size)
	{
		int ax = 0;
		int ay = 0;
		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] == '\n')
			{
				ax = 0;
				ay ++;
			}
			else
			{
				renderChar(text[i], x+ax*size*.5, y+ay*size, size);
				ax++;
			}
		}
	}
	
	vec2 Font::textSize(std::string text, int size)
	{
		int mx(0), my(0);
		int ax = 0;
		int ay = 0;
		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] == '\n')
			{
				if (ax > mx) mx = ax;
				ax = 0;
				ay ++;
			}
			else
				ax++;
		}
		if (ax > mx) mx = ax;
		my = ay;
		vec2 r((mx+1)*size*.5, (my+1)*size);
		return r;
	}
}

