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

#pragma once

#include <vector>
#include "pstypes.h"
#include "vecmat.h"

//A sortable element is used to batch up elements by their texture and lightmap handle, if used. 
struct SortableElement
{
	int element;
	short texturehandle;
	short lmhandle;

	friend bool operator<(const SortableElement& l, const SortableElement& r)
	{
		uint lh = l.texturehandle | l.lmhandle << 16;
		uint rh = r.texturehandle | r.lmhandle << 16;

		return lh < rh;
	}
};

struct RendVertex
{
	vector position;
	uint8_t r, g, b, a;
	vector normal;
	int lmpage;
	float u1, v1;
	float u2, v2;
	float uslide, vslide; //only slide uv1 for the moment
};

//A batch of 0-2 texture handles.
struct MeshBatch
{
	int primaryhandle;
	int secondaryhandle;
	int vertexoffset, vertexcount;
	int indexoffset, indexcount;
};

class MeshBuilder
{
	unsigned int m_handle; 
	unsigned int m_verthandle, m_indexhandle;
	bool m_initialized;

	std::vector<MeshBatch> m_interactions;
	std::vector<RendVertex> m_vertices;
	std::vector<uint16_t> m_indicies;

	//Updates the counts of the last batch if relevant. 
	void UpdateLastBatch();
public:
	MeshBuilder();

	//Starts a solid batch with no textures. 
	//Do not mix this with any of the textured forms.
	//These probably could take shader program numbers to deal with that but eh
	void StartBatchSolid();

	//Starts a textured batch with one texture.
	void StartBatchOneTex(int handle);
	//Starts a textured batch with two textures.
	void StartBatchTwoTex(int handle, int handle2);

	//Sets the vertices for this mesh builder to use. 
	void SetVertices(int numverts, RendVertex* vertices);

	//Sets the indicies for this mesh builder to use. Optional.
	//If set, drawing the mesh will use the index buffer while drawing.
	void SetIndicies(int numindices, short* indicies);

	//Updates the buffer. When called for the first time, will create all the relevant state
	//Can be called again to update the buffers.
	void Build();

	void Destroy();

	//For dynamic meshes
	void Reset();

	//Draws the mesh with the currently bound shader.
	void Draw() const;

	int NumVertices() const
	{
		return m_vertices.size();
	}
};
