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

namespace AGuiSy {
	Entry::Entry(ElementStyle &_style, EventHandler &_handler):
		Element(_style,_handler)
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
					handler.onEvent(*this, e);
				}
			}
			else if (state == STATE_HOVER)
			{
				state = STATE_NORMAL;
				Event e(EVENT_MOUSEOUT);
				handler.onEvent(*this,e);
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (state == STATE_HOVER)
			{
				state = STATE_PRESS;
				Event e(EVENT_MOUSEDOWN);
				handler.onEvent(*this,e);
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
				handler.onEvent(*this,e);
			}
		}
		if (e.type == SDL_KEYDOWN)
		{
			text += (char)e.key.keysym.unicode;
			Event ne(EVENT_KEYDOWN,e.key.keysym.sym,e.key.keysym.unicode);
			handler.onEvent(*this,ne);
		}
	}
}
