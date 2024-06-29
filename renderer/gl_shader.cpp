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
#include <string.h>
#include <string>
#include "gl_shader.h"
#include "pserror.h"

GLuint commonbuffername;
GLuint legacycommonbuffername;

void opengl_InitCommonBuffer(void)
{
	glGenBuffers(1, &commonbuffername);
	glBindBuffer(GL_COPY_WRITE_BUFFER, commonbuffername);
	glBufferData(GL_COPY_WRITE_BUFFER, sizeof(CommonBlock), nullptr, GL_DYNAMIC_READ);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, commonbuffername);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		Int3();

	//Ensure this is always ready for usage later. 

	//The legacy common buffer uses the ortho matrix as a passthrough.
	glGenBuffers(1, &legacycommonbuffername);
	glBindBuffer(GL_COPY_WRITE_BUFFER, legacycommonbuffername);
	glBufferData(GL_COPY_WRITE_BUFFER, sizeof(CommonBlock), nullptr, GL_DYNAMIC_READ);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, legacycommonbuffername);

	err = glGetError();
	if (err != GL_NO_ERROR)
		Int3();
}

void rend_UpdateCommon(float* projection, float* modelview)
{
	CommonBlock newblock;
	memcpy(newblock.projection, projection, sizeof(newblock.projection));
	memcpy(newblock.modelview, modelview, sizeof(newblock.modelview));

	glBindBuffer(GL_COPY_WRITE_BUFFER, commonbuffername);
	glBufferSubData(GL_COPY_WRITE_BUFFER, 0, sizeof(CommonBlock), &newblock);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		Int3();
}

void GL_UpdateLegacyBlock(float* projection, float* modelview)
{
	CommonBlock newblock;
	memcpy(newblock.projection, projection, sizeof(newblock.projection));
	memcpy(newblock.modelview, modelview, sizeof(newblock.modelview));

	glBindBuffer(GL_COPY_WRITE_BUFFER, legacycommonbuffername);
	glBufferSubData(GL_COPY_WRITE_BUFFER, 0, sizeof(CommonBlock), &newblock);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		Int3();
}

static GLuint CompileShader(GLenum type, int numstrs, const char** src, GLint* lengths)
{
	GLuint name = glCreateShader(type);
	glShaderSource(name, numstrs, src, lengths);
	glCompileShader(name);
	GLint status;
	glGetShaderiv(name, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(name, GL_INFO_LOG_LENGTH, &length);
		char* buf = new char[length];
		glGetShaderInfoLog(name, length, &length, buf);

		mprintf((1, "%s\n", buf));
		Error("CompileShader: Failed to compile shader! This error message needs more context..\n%s", buf);
	}

	return name;
}

void ShaderProgram::CreateCommonBindings(int bindindex)
{
	Use();

	//Find colortexture
	GLint index = glGetUniformLocation(m_name, "colortexture");
	if (index != -1)
		glUniform1i(index, 0); //Set to GL_TEXTURE0

	//Find lightmaptexture
	index = glGetUniformLocation(m_name, "lightmaptexture");
	if (index != -1)
		glUniform1i(index, 1); //Set to GL_TEXTURE1

	//Find CommonBlock
	GLuint uboindex = glGetUniformBlockIndex(m_name, "CommonBlock");
	if (uboindex != GL_INVALID_INDEX)
	{
		//Bind to GL_UNIFORM_BUFFER bindindex. This is so that "legacy" shaders can have the passthrough matricies. 
		glUniformBlockBinding(m_name, uboindex, bindindex);
	}

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		Int3();

	glUseProgram(0);
}

void ShaderProgram::AttachSource(const char* vertexsource, const char* fragsource)
{
	GLint vertexsourcelen = strlen(vertexsource);
	GLint fragsourcelen = strlen(fragsource);
	GLuint vertexprog = CompileShader(GL_VERTEX_SHADER, 1, &vertexsource, &vertexsourcelen);
	GLuint fragmentprog = CompileShader(GL_FRAGMENT_SHADER, 1, &fragsource, &fragsourcelen);

	m_name = glCreateProgram();
	glAttachShader(m_name, vertexprog);
	glAttachShader(m_name, fragmentprog);
	glLinkProgram(m_name);
	GLint status;
	glGetProgramiv(m_name, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &length);
		char* buf = new char[length];
		glGetProgramInfoLog(m_name, length, &length, buf);

		Error("ShaderProgram::AttachSource: Failed to link program! This error message needs more context..\n%s", buf);
	}

	glDeleteShader(vertexprog);
	glDeleteShader(fragmentprog);

	CreateCommonBindings(0);
}

void ShaderProgram::AttachSourcePreprocess(const char* vertexsource, const char* fragsource, bool textured, bool lightmapped, bool speculared)
{
	const char* vertexstrs[3];
	GLint vertexlens[3];
	const char* fragstrs[3];
	GLint fraglens[3];

	vertexstrs[0] = fragstrs[0] = "#version 330 core\n";
	vertexlens[0] = fraglens[0] = strlen(vertexstrs[0]);

	std::string preprocessorstr;
	if (textured)
		preprocessorstr.append("#define USE_TEXTURING\n");
	if (lightmapped)
		preprocessorstr.append("#define USE_LIGHTMAP\n");
	if (speculared)
		preprocessorstr.append("#define USE_SPECULAR\n");

	vertexstrs[1] = fragstrs[1] = preprocessorstr.c_str();
	vertexlens[1] = fraglens[1] = preprocessorstr.size();

	vertexstrs[2] = vertexsource; vertexlens[2] = strlen(vertexsource);
	fragstrs[2] = fragsource; fraglens[2] = strlen(fragsource);

	GLuint vertexprog = CompileShader(GL_VERTEX_SHADER, 3, vertexstrs, vertexlens);
	GLuint fragmentprog = CompileShader(GL_FRAGMENT_SHADER, 3, fragstrs, fraglens);

	m_name = glCreateProgram();
	glAttachShader(m_name, vertexprog);
	glAttachShader(m_name, fragmentprog);
	glLinkProgram(m_name);
	GLint status;
	glGetProgramiv(m_name, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &length);
		char* buf = new char[length];
		glGetProgramInfoLog(m_name, length, &length, buf);

		Error("ShaderProgram::AttachSource: Failed to link program! This error message needs more context..\n%s", buf);
	}

	glDeleteShader(vertexprog);
	glDeleteShader(fragmentprog);

	//Always use the legacy block with these preprocessed shaders, for now.
	CreateCommonBindings(1);
}

GLint ShaderProgram::FindUniform(const char* uniform)
{
	return glGetUniformLocation(m_name, uniform);
}

void ShaderProgram::Destroy()
{
	glUseProgram(0);
	glDeleteProgram(m_name);
	m_name = 0;
}
