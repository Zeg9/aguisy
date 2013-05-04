/*
 * ProgressBar.h
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


#ifndef __AGUISY_PROGRESSBAR_H__
#define __AGUISY_PROGRESSBAR_H__

#include <AGuiSy/Element.h>
#include <string>

namespace AGuiSy {
	class ProgressBar : public Element {
		public:
			ProgressBar(ElementStyle &_style, EventHandler *_handler);
			virtual void render();
			virtual void event(SDL_Event &e);
			virtual std::string getRenderText();
		//private:
			uint8_t percent;
	};
}

#endif /* __AGUISY_PROGRESSBAR_H__ */

