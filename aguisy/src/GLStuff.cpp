/*
 * GLStuff.cpp
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
#include <GL/glew.h>
#include <iostream> // TODO: use a global error and debug stream
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AGuiSy {
	GLuint quadVertexBuffer = 0;
	GLuint quadUVBuffer = 0;
	GLuint program = 0;
	void setQuadUVs(float uvx1, float uvy1, float uvx2, float uvy2)
	{
		GLfloat quadUVs[] = {
			uvx1,uvy1,
			uvx1,uvy2,
			uvx2,uvy1,
			uvx2,uvy2,
			uvx2,uvy1,
			uvx1,uvy2,
		};
		glBindBuffer(GL_ARRAY_BUFFER, quadUVBuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(GLfloat)*6*2, quadUVs, GL_STATIC_DRAW);
	}
	void initGLStuff()
	{
		// upload the quad vertices to the buffer
		glGenBuffers(1,&quadVertexBuffer);
		GLfloat quadVertices[] = {
			0,0,0,
			0,1,0,
			1,0,0,
			1,1,0,
			1,0,0,
			0,1,0,
		};
		glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(GLfloat)*6*3, quadVertices, GL_STATIC_DRAW);
		
		// same for uvs
		glGenBuffers(1,&quadUVBuffer);
		setQuadUVs(0,0,1,1);
		
		//// SHADERS ////
		
		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Hard-coded shaders
		// Any other way toinclude them at compile time,
		// without depending on external files ?
		std::string VertexShaderCode =
			"#version 120" "\n"
			"attribute vec3 vertexPosition;" "\n"
			"attribute vec2 vertexUV;" "\n"
			"varying vec2 uv;" "\n"
			"uniform mat4 MVP;" "\n"
			"void main()" "\n"
			"{" "\n"
			"	vec4 v = vec4(vertexPosition, 1.0);" "\n"
			"	gl_Position = MVP*v;" "\n"
			"	uv = vertexUV;" "\n"
			"}" "\n";
			
		std::string FragmentShaderCode = 
			"#version 120" "\n"
			"varying vec2 uv;" "\n"
			"uniform vec4 color;" "\n"
			"uniform sampler2D textureSampler;" "\n"
			"void main()" "\n"
			"{" "\n"
			"	gl_FragColor = texture2D(textureSampler,uv)*color;" "\n"
			"}" "\n";
		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile Vertex Shader
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		// TODO Check shaders and programs if some debug bool is true
		/*glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if ( InfoLogLength > 0 ){
			std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			std::cerr << &VertexShaderErrorMessage[0] << std::endl;
		}*/

		// Compile Fragment Shader
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		/*glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if ( InfoLogLength > 0 ){
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			std::cerr << &FragmentShaderErrorMessage[0] << std::endl;
		}*/

		// Link the program
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		/*glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if ( InfoLogLength > 0 ){
			std::vector<char> ProgramErrorMessage(InfoLogLength+1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			std::cerr << &ProgramErrorMessage[0] << std::endl;
		}*/

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		program = ProgramID;
	}
	void drawQuad(int x, int y, int w, int h, GLuint texture)
	{
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		int width = 640;
		int height = 480;
		// TODO get width and height with glGet(GL_VIEWPORT)
		glm::vec4 color (1.0f);
		// TODO argument for color
		glm::mat4 projection = glm::ortho(0.0f,(float)width,(float)height,0.0f,0.0f,1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 model(1.0f);
		model = glm::translate(model,glm::vec3((float)x,(float)y,0.0f));
		model = glm::scale(model,glm::vec3((float)w,(float)h,1.0f));
		glm::mat4 mvp = projection*view*model;
		
		glUseProgram(program);
	
		GLuint matrixID = glGetUniformLocation(program, "MVP");
		GLuint colorID = glGetUniformLocation(program, "color");
		GLuint textureID = glGetUniformLocation(program, "textureSampler");
		GLuint vertexPositionID = glGetAttribLocation(program,"vertexPosition");
		GLuint vertexUVID = glGetAttribLocation(program,"vertexUV");
	
		glUniformMatrix4fv(matrixID,1,GL_FALSE,&mvp[0][0]);
		glUniform4fv(colorID,1,&color[0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(textureID, 0);
	
		glEnableVertexAttribArray(vertexPositionID);
		glBindBuffer(GL_ARRAY_BUFFER,quadVertexBuffer);
		glVertexAttribPointer(vertexPositionID,3,GL_FLOAT,GL_FALSE,0,0);
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER,quadUVBuffer); // TODO uv buffer
		glVertexAttribPointer(vertexUVID,2,GL_FLOAT,GL_FALSE,0,0);
		glDrawArrays(GL_TRIANGLES,0,6);
		glDisableVertexAttribArray(vertexPositionID);
		glDisableVertexAttribArray(vertexUVID);
	}
	void drawQuad(int x, int y, int w, int h, GLuint texture,
		float uvx1, float uvy1, float uvx2, float uvy2)
	{
		setQuadUVs(uvx1,uvy1,uvx2,uvy2);
		drawQuad(x,y,w,h,texture);
		setQuadUVs(0,0,1,1);
	}
}

