/*
 * Element.h
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

#ifndef __AGUISY_ELEMENT_H__
#define __AGUISY_ELEMENT_H__

#include <SDL/SDL.h>
#include <AGuiSy/Types.h>
#include <AGuiSy/State.h>
#include <string>

namespace AGuiSy {
	class ElementStyle;
	class EventHandler;

	class Element
	{
		public:
			Element(ElementStyle &_style, EventHandler &_handler);
			virtual ~Element();
			virtual void render();
			virtual void event(SDL_Event &e) = 0;
			virtual std::string getRenderText();
			vec2 getPos();
			void setPos(int _x, int _y);
			vec2 getSize();
			void setSize(int _w, int _h);
			std::string getText();
			void setText(std::string _text);
			void setEventHandler(EventHandler &_handler);
		protected:
			ElementStyle &style;
			int x, y, w, h;
			std::string text;
			State state;
			EventHandler &handler;
	};
}

#endif /* __AGUISY_ELEMENT_H__ */

