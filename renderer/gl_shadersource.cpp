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

const char* blitVertexSrc =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec2 position;\n"
"layout(location = 1) in vec2 uv;\n"
"\n"
"out vec2 outuv;\n"
"\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 0.0, 1.0);\n"
"outuv = uv;"
"}\n"
"";

const char* blitFragmentSrc =
"#version 330 core\n"
"\n"
"in vec2 outuv;\n"
"\n"
"out vec4 color;\n"
"\n "
"uniform sampler2D heh;\n"
"uniform float gamma;\n"
"\n"
"void main()\n"
"{\n"
"vec4 sourcecolor = texture(heh, outuv);\n"
"color = vec4(pow(sourcecolor.rgb, vec3(gamma)), sourcecolor.a);\n"
"}\n"
"";

const char* testVertexSrc = 
"#version 330 core\n"
"\n"
"layout(std140) uniform CommonBlock\n"
"{\n"
"	mat4 projection;\n"
"	mat4 modelview;\n"
"} commons;\n"
"\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 4) in vec2 uv;\n"
"layout(location = 5) in vec2 uv2;\n"
"\n"
"out vec2 outuv;\n"
"out vec2 outuv2;\n"
"\n"
"void main()\n"
"{\n"
"	vec4 temp = commons.modelview * vec4(position, 1.0);\n"
"	gl_Position = commons.projection * vec4(temp.xy, -temp.z, temp.w);\n"
"	outuv = uv;\n"
"	outuv2 = uv2;\n"
"}\n"
"";

const char* testFragmentSrc = 
"#version 330 core\n"
"\n"
"uniform sampler2D colortexture;\n"
"uniform sampler2D lightmaptexture;\n"
"\n"
"in vec2 outuv;\n"
"in vec2 outuv2;\n"
"\n"
"out vec4 color;\n"
"\n"
"void main()\n"
"{\n"
"	vec4 basecolor = texture(colortexture, outuv);\n"
"	color = vec4(basecolor.rgb * texture(lightmaptexture, outuv2).rgb, basecolor.a);\n"
"}\n"
"";

const char* genericVertexBody =
"layout(std140) uniform CommonBlock\n"
"{\n"
"	mat4 projection;\n"
"	mat4 modelview;\n"
"} commons;\n"
"\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec4 color;\n"
"layout(location = 2) in vec4 uv;\n"
"layout(location = 3) in vec4 uv2;\n"
"\n"
"out vec4 outcolor;\n"
"#if defined(USE_TEXTURING)\n"
"out vec4 outuv;\n"
"#if defined(USE_LIGHTMAP)\n"
"out vec4 outuv2;\n"
"#endif\n"
"#endif\n"
"\n"
"void main()\n"
"{\n"
"	gl_Position = commons.projection * commons.modelview * vec4(position, 1.0);\n"
"	outcolor = color;\n"
"	#if defined(USE_TEXTURING)\n"
"		outuv = uv;\n"
"		#if defined(USE_LIGHTMAP)\n"
"			outuv2 = uv2;\n"
"		#endif\n"
"	#endif\n"
"}\n"
"";

const char* genericFragBody =
"#if defined(USE_TEXTURING)\n"
"uniform sampler2D colortexture;\n"
"#if defined(USE_LIGHTMAP)\n"
"uniform sampler2D lightmaptexture;\n"
"#endif\n"
"#endif\n"
"\n"
"in vec4 outcolor;\n"
"#if defined(USE_TEXTURING)\n"
"in vec4 outuv;\n"
"#if defined(USE_LIGHTMAP)\n"
"in vec4 outuv2;\n"
"#endif\n"
"#endif\n"
"\n"
"out vec4 color;\n"
"\n"
"void main()\n"
"{\n"
"	#if defined(USE_SPECULAR)\n"
"		color = vec4(outcolor.rgb, texture(colortexture, outuv.xy / outuv.w).a * outcolor.a);\n"
"	#elif defined(USE_TEXTURING) && defined(USE_LIGHTMAP)\n"
"		color = texture(colortexture, outuv.xy / outuv.w) * texture(lightmaptexture, outuv2.xy / outuv2.w) * outcolor;\n"
"	#elif defined(USE_TEXTURING)\n"
"		color = texture(colortexture, outuv.xy / outuv.w) * outcolor;\n"
"	#else\n"
"		color = outcolor;\n"
"	#endif\n"
"}\n"
"";