/*
* Descent 3: Piccu Engine
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

#include "gl_local.h"
#include "gl_mesh.h"

MeshBuilder::MeshBuilder()
{
	m_handle = m_verthandle = m_indexhandle = 0;
	m_initialized = false;
}

void MeshBuilder::UpdateLastBatch()
{
	if (m_interactions.empty())
		return;

	MeshBatch& lastbatch = m_interactions.back();
	lastbatch.vertexcount = m_vertices.size() - lastbatch.vertexoffset;
	lastbatch.indexcount = m_indicies.size() - lastbatch.indexoffset;
}

void MeshBuilder::StartBatchSolid()
{
	UpdateLastBatch();

	MeshBatch batch;
	batch.primaryhandle = batch.secondaryhandle = -1;
	batch.vertexoffset = m_vertices.size();
	batch.vertexcount = 0;
	batch.indexoffset = m_indicies.size();
	batch.indexcount = 0;
	m_interactions.push_back(batch);
}

void MeshBuilder::StartBatchOneTex(int handle)
{
	UpdateLastBatch();

	MeshBatch batch;
	batch.primaryhandle = handle;
	batch.secondaryhandle = -1;
	batch.vertexoffset = m_vertices.size();
	batch.vertexcount = 0;
	batch.indexoffset = m_indicies.size();
	batch.indexcount = 0;
	m_interactions.push_back(batch);
}

void MeshBuilder::StartBatchTwoTex(int handle, int handle2)
{
	UpdateLastBatch();

	MeshBatch batch;
	batch.primaryhandle = handle;
	batch.secondaryhandle = handle2;
	batch.vertexoffset = m_vertices.size();
	batch.vertexcount = 0;
	batch.indexoffset = m_indicies.size();
	batch.indexcount = 0;
	m_interactions.push_back(batch);
}

void MeshBuilder::SetVertices(int numverts, RendVertex* vertices)
{
	//This needs some optimization
	for (int i = 0; i < numverts; i++)
		m_vertices.push_back(vertices[i]);
}

void MeshBuilder::SetIndicies(int numindices, short* indicies)
{
	for (int i = 0; i < numindices; i++)
		m_indicies.push_back(indicies[i]);
}

void MeshBuilder::Build()
{
	if (m_handle)
		Destroy();

	UpdateLastBatch();

	if (m_handle == 0)
		glGenVertexArrays(1, &m_handle);

	glBindVertexArray(m_handle);

	if (m_verthandle == 0)
		glGenBuffers(1, &m_verthandle);

	glBindBuffer(GL_ARRAY_BUFFER, m_verthandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RendVertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	if (!m_initialized)
	{
		//Create the standard vertex attributes
		//Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RendVertex), (void*)offsetof(RendVertex, position));

		//Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_BYTE, GL_TRUE, sizeof(RendVertex), (void*)offsetof(RendVertex, r));

		//Normal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(RendVertex), (void*)offsetof(RendVertex, normal));

		//Lightmap page
		glEnableVertexAttribArray(3);
		glVertexAttribIPointer(3, 1, GL_INT, sizeof(RendVertex), (void*)offsetof(RendVertex, lmpage));

		//Base UV
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(RendVertex), (void*)offsetof(RendVertex, u1));

		//Overlay UV
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(RendVertex), (void*)offsetof(RendVertex, u2));

		//UV slide
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(RendVertex), (void*)offsetof(RendVertex, u2));
	}

	//Check if indicies are being used
	if (!m_indicies.empty())
	{
		if (!m_indexhandle)
			glGenBuffers(1, &m_indexhandle);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexhandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * m_indicies.size(), m_indicies.data(), GL_STATIC_DRAW);
	}

	//All the data is GPU side now, so no sense in keeping this around
	m_vertices.clear();
	m_indicies.clear();

	GL_UseDrawVAO();
	//TODO: Once everything is using GL 3.3 systems this shouldn't be done anymore
	//glBindVertexArray(0);
}

void MeshBuilder::Destroy()
{
	if (m_indexhandle)
	{
		glDeleteBuffers(1, &m_indexhandle);
		m_indexhandle = 0;
	}

	if (m_verthandle)
	{
		glDeleteBuffers(1, &m_verthandle);
		m_verthandle = 0;
	}

	if (m_handle)
	{
		glDeleteVertexArrays(1, &m_handle);
		m_handle = 0;
	}

	m_vertices.clear();
	m_indicies.clear();
	m_interactions.clear();
}

void MeshBuilder::Reset()
{
	m_vertices.clear();
	m_indicies.clear();
	m_interactions.clear();
}

void MeshBuilder::Draw() const
{
	glBindVertexArray(m_handle);
	if (m_indexhandle)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexhandle);

	for (const MeshBatch& batch : m_interactions)
	{
		//Why have I not made a "make bitmap current" function yet?
		if (batch.primaryhandle >= 0)
		{
			opengl_MakeBitmapCurrent(batch.primaryhandle, MAP_TYPE_BITMAP, 0);
			opengl_MakeWrapTypeCurrent(batch.primaryhandle, MAP_TYPE_BITMAP, 0);
			opengl_MakeFilterTypeCurrent(batch.primaryhandle, MAP_TYPE_BITMAP, 0);
		}
		if (batch.secondaryhandle >= 0)
		{
			opengl_MakeBitmapCurrent(batch.secondaryhandle, MAP_TYPE_LIGHTMAP, 1);
			opengl_MakeWrapTypeCurrent(batch.secondaryhandle, MAP_TYPE_LIGHTMAP, 1);
			opengl_MakeFilterTypeCurrent(batch.secondaryhandle, MAP_TYPE_LIGHTMAP, 1);
		}
		//Eventually third overlay type for bump mapping?

		if (m_indexhandle)
			glDrawElements(GL_TRIANGLES, batch.indexcount, GL_UNSIGNED_SHORT, (const void*)(batch.indexoffset * sizeof(uint16_t)));
		else
			glDrawArrays(GL_TRIANGLES, batch.vertexoffset, batch.vertexcount);

#ifndef NDEBUG
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
			Int3();
#endif
	}

	GL_UseDrawVAO();
}
