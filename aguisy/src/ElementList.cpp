/*
 * ElementList.cpp
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

#include "ElementList.h"
#include <stack>

#define FOR_IN_ELEMENTS for (std::list<Element*>::iterator it = elementList.begin();\
			it != elementList.end(); it++)

namespace AGuiSy {
	std::list<Element*> elementList;
	bool endloop = false;
	void addElement(Element *el)
	{
		elementList.push_back(el);
	}
	Element *getElement(std::string name)
	{
		FOR_IN_ELEMENTS
			if ((*it)->getName() == name)
				return *it;
		return 0;
	}
	void deleteElement(Element *el)
	{
		if (!el) return;
		delete el;
		elementList.remove(el);
		endloop = true;
	}
	void deleteElement(std::string name)
	{
		deleteElement(getElement(name));
	}
	void clearElements()
	{
		std::stack<Element*> toremove;
		FOR_IN_ELEMENTS
			toremove.push(*it);
		while (!toremove.empty())
		{
			deleteElement(toremove.top());
			toremove.pop();
		}
	}
	
	void render()
	{
		FOR_IN_ELEMENTS
			(*it)->render();
	}
	void event(SDL_Event &e)
	{
		endloop = false;
		FOR_IN_ELEMENTS
		{
			(*it)->event(e);
			if (endloop) break;
		}
	}
}
