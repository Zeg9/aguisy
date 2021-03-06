/*
 * Types.cpp
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

#include "Types.h"
#include <sstream>
namespace AGuiSy {
	vec2::vec2() : x(0), y(0) {}
	vec2::vec2(int _x, int _y) : x(_x), y(_y) {}
	vec2::vec2(std::string fromString)
	{
		std::string tmp(""), sx(""), sy("");
		for (int i = 0; i < fromString.size(); i++)
		{
			if (fromString[i]==',') { sx = tmp; tmp = ""; }
			else tmp += fromString[i];
		}
		sy = tmp;
		std::istringstream issx(sx);
		issx >> x;
		std::istringstream issy(sy);
		issy >> y;
	}
}
