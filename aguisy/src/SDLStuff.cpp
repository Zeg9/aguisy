/*
 * SDLStuff.cpp
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

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <AGuiSy/SDLStuff.h>

#include <iostream>

namespace AGuiSy {
	GLuint loadTexture(std::string path)
	{
		GLuint glID;
		SDL_Surface * picture_surface = NULL;
		SDL_Surface *gl_surface = NULL;
		SDL_Surface * gl_fliped_surface = NULL;
		Uint32 rmask, gmask, bmask, amask;
		picture_surface = IMG_Load(path.c_str());
		if (picture_surface == NULL)
		{
			std::cerr << "Couldn't load texture: " << path << std::endl;
			return 0;
		}
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif
		SDL_PixelFormat format = *(picture_surface->format);
		format.BitsPerPixel = 32;
		format.BytesPerPixel = 4;
		format.Rmask = rmask;
		format.Gmask = gmask;
		format.Bmask = bmask;
		format.Amask = amask;
		gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);
		glGenTextures(1, &glID);
		glBindTexture(GL_TEXTURE_2D, glID);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_surface->w,
				gl_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
				gl_surface->pixels);
		// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Generate mipmaps, by the way.
		glGenerateMipmap(GL_TEXTURE_2D);
		SDL_FreeSurface(gl_surface);
		SDL_FreeSurface(picture_surface);
		return glID;
	}
}

