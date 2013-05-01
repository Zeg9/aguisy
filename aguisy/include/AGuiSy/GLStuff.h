/*
 * GLStuff.h
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

#ifndef __AGUISY_GLSTUFF_H__
#define __AGUISY_GLSTUFF_H__

#include <GL/glew.h>

namespace AGuiSy {
	extern GLuint quadVertexBuffer;
	extern GLuint quadUVBuffer;
	extern GLuint program;
	void initGLStuff();
	void setQuadUVs(float uvx1, float uvy1, float uvx2, float uvy2);
	void drawQuad(int x, int y, int w, int h, GLuint texture);
	void drawQuad(int x, int y, int w, int h, GLuint texture,
		float uvx1, float uvy1, float uvx2, float uvy2);
}

#endif /* __AGUISY_GLSTUFF_H__ */

