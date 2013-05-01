/*
 * Entry.cpp
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

#include <AGuiSy/Entry.h>
#include <AGuiSy/Event.h>
#include <AGuiSy/Style.h>

namespace AGuiSy {
	Entry::Entry(ElementStyle &_style, EventHandler *_handler):
		Element(_style,_handler),
		hideText(false)
	{}
	void Entry::event(SDL_Event &e)
	{
		if (e.type == SDL_MOUSEMOTION)
		{
			if (e.motion.x >= x
			 && e.motion.x <= x+w
			 && e.motion.y >= y
			 && e.motion.y <= y+h)
			{
				if (state == STATE_NORMAL)
				{
					state = STATE_HOVER;
					Event e (EVENT_MOUSEIN);
					handler->onEvent(*this, e);
				}
			}
			else if (state == STATE_HOVER)
			{
				state = STATE_NORMAL;
				Event e(EVENT_MOUSEOUT);
				handler->onEvent(*this,e);
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (state == STATE_HOVER)
			{
				state = STATE_PRESS;
				Event e(EVENT_MOUSEDOWN);
				handler->onEvent(*this,e);
			}
			else if (state == STATE_PRESS && !(
			    e.motion.x >= x
			 && e.motion.x <= x+w
			 && e.motion.y >= y
			 && e.motion.y <= y+h))
			{
				if (e.button.x >= x
				 && e.button.x <= x+w
				 && e.button.y >= y
				 && e.button.y <= y+h)
					state = STATE_HOVER;
				else
					state = STATE_NORMAL;
				Event e(EVENT_MOUSEUP);
				handler->onEvent(*this,e);
			}
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (state == STATE_PRESS) {
				if (e.key.keysym.sym == SDLK_BACKSPACE)
					text = text.substr(0,text.size()-1);
				char c = e.key.keysym.unicode;
				if (c >= ' ' && c <= '~')
					text += c;
				Event ne(EVENT_KEYDOWN,e.key.keysym.sym,e.key.keysym.unicode);
				handler->onEvent(*this,ne);
			}
		}
	}
	void Entry::render()
	{
		Element::render();
		if (state == STATE_PRESS && SDL_GetTicks()%1000 < 500)
		{
			std::string t = getRenderText();
			int fs = style.getFontSize();
			vec2 s = style.getFont().textSize(t,fs);
			style.getFont().renderChar('|', x+w/2+s.x/2-fs/2, y+h/2-s.y/2, fs);
		}
	}
	std::string Entry::getRenderText()
	{
		std::string t = Element::getRenderText();
		if (getHideText())
		{
			for (int i = 0; i < t.size(); i++)
				t[i] = '*';
		}
		return t;
	}
	bool Entry::getHideText() { return hideText; }
	void Entry::setHideText(bool hide) { hideText = hide; }
}
