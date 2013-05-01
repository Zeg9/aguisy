/*
 * Init.cpp
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

#include "GLStuff.h"
#include "Style.h"
#include "Event.h"

namespace AGuiSy {
	void init(std::string stylePath, EventHandler*handlerInstance)
	{
		initGLStuff();
		mainStyle = new Style(stylePath);
		mainHandler = handlerInstance;
	}
	void quit()
	{
		if (mainStyle != 0) delete mainStyle;
		if (mainHandler != 0) delete mainHandler;
	}
}
