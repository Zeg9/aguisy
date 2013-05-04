/*
 * Parser.cpp
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

#include "Parser.h"
#include "Event.h"
#include "Style.h"
#include "Element.h"
#include "Button.h"
#include "Entry.h"
#include "ProgressBar.h"
#include "ElementList.h"

#include <iostream>

namespace AGuiSy {
	void parseElements(std::string def)
	{
		std::string tmp(""), key("");
		std::string type("");
		bool indef = false;
		Element *e(0);
		for (int i = 0; i < def.size(); i++)
		{
			if (!indef) {
				if (def[i] == '[') {
					type = tmp;
					tmp = "";
					if (type == "button") {
						e = new Button(mainStyle->button,mainHandler);
					} else if (type == "entry") {
						e = new Entry(mainStyle->entry,mainHandler);
					} else if (type == "progressbar") {
						e = new ProgressBar(mainStyle->button,mainHandler);
					}
					indef = true;
				} else {
					tmp += def[i];
				}
			} else {
				if (def[i] == ']') {
					if (e)
					{
						deleteElement(e->getName());
						addElement(e);
						e = 0;
					}
					indef = false;
				} else if (def[i] == '=') {
					key = tmp;
					tmp = "";
				} else if (def[i] == ';') {
					std::string val = tmp;
					tmp = "";
					if (e!=0)
					{
						if (key == "pos")
							e->setPos(vec2(val));
						if (key == "size")
							e->setSize(vec2(val));
						if (key == "name")
							e->setName(val);
						if (key == "text")
							e->setText(val);
						if (type == "entry")
						{
							Entry *entry = (Entry*)e;
							if (key == "hidetext")
							{
								if (val == "true" || val == "1")
									entry->setHideText(true);
							}
						}
					}
				} else {
					tmp += def[i];
				}
			}
		}
	}
}
