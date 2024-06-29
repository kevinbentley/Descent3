/*
* Piccu Engine
* Copyright (C) 2024 SaladBadger
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <glad/gl.h>

struct CommonBlock
{
	float projection[16];
	float modelview[16];
};

void opengl_InitCommonBuffer(void);

class ShaderProgram
{
	GLuint m_name;
	//CreateCommonBindings will find common uniforms and set their default bindings.
	//This includes the common block, which must be named "common",
	//and sampler2Ds named "colortexture", "lightmaptexture", and others later.
	void CreateCommonBindings(int bindindex);
public:
	ShaderProgram()
	{
		m_name = 0;
	}

	void AttachSource(const char* vertexsource, const char* fragsource);
	//Attaches strings with some preprocessor statements. 
	//Defines USE_TEXTURING if textured is true.
	//Defines USE_LIGHTMAP if lightmapped is true.
	//Defines USE_SPECULAR if speculared is true. 
	void AttachSourcePreprocess(const char* vertexsource, const char* fragsource, bool textured, bool lightmapped, bool speculared);
	GLint FindUniform(const char* uniform);
	void Destroy();

	void Use()
	{
		glUseProgram(m_name);
	}

	GLuint Handle() const
	{
		return m_name;
	}
};
