/*
 * Entry.h
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

#include <AGuiSy/Element.h>

namespace AGuiSy {
	class Entry : public Element {
		public:
			Entry(ElementStyle &_style, EventHandler *_handler);
			virtual void event(SDL_Event &e);
			virtual void render();
			virtual std::string getRenderText();
			bool getHideText();
			void setHideText(bool hide);
		protected:
			bool hideText;
	};
}
