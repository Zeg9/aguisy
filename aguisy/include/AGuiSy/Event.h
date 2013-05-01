/*
 * Event.h
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

#ifndef __AGUISY_EVENT_H__
#define __AGUISY_EVENT_H__

#include <SDL/SDL.h>
#include <AGuiSy/Element.h>

namespace AGuiSy {
	enum EventType {
		EVENT_MOUSEIN,
		EVENT_MOUSEOUT,
		EVENT_MOUSEDOWN,
		EVENT_MOUSEUP,
		EVENT_KEYDOWN,
		EVENT_KEYUP,
	};

	struct Event {
		Event(EventType _type, uint8_t _keycode=0, uint16_t _unicode=0);
		EventType type;
		uint8_t keycode;
		uint16_t unicode;
	};

	class EventHandler {
		public:
			virtual void onEvent(Element &element, Event &event) = 0;
	};
	extern EventHandler *mainHandler;
}

#endif /* __AGUISY_EVENT_H__ */

