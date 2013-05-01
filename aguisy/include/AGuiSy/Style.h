/*
 * Style.h
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

#ifndef __AGUISY_STYLE_H__
#define __AGUISY_STYLE_H__

#include <GL/glew.h>
#include <string>
#include <AGuiSy/State.h>
#include <AGuiSy/Font.h>

namespace AGuiSy {
	class ElementStyle
	{
		public:
			// How to create element styles:
			// - Name your textures *_normal.png, *_hover.png,
			//                      *_press.png, *_inactive.png
			//   * being any prefix of your choice, for example button
			// - Put them in some folder, here we'll take textures/gui/
			// - Choose some font, here: textures/gui/font.png
			// - Load the theme: ElementStyle style("<folder>/<prefix>","<font>");
			//   e.g. ElementStyle style("textures/gui/button","textures/gui/font.png");
			ElementStyle(std::string path, std::string fontpath);
			~ElementStyle();
			GLuint getTexture(State s);
			int getOffset();
			int getSize();
			// For the moment offset and size are hardcoded. (FIXME)
			// Later we'll add a *.style file or somehting like that for config.
			Font &getFont();
			int getFontSize();
		protected:
			GLuint normal;
			GLuint hover;
			GLuint press;
			GLuint inactive;
			Font font;
	};
	struct Style
	{
		Style(std::string path);
		ElementStyle button;
		ElementStyle entry;
	};
	extern Style* mainStyle;
}

#endif /* __AGUISY_STYLE_H__ */

