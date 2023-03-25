#pragma once
#include <math.h>
#include "Vector3.h"
#include "Vector2.h"

class VertexMesh
{
public:
	Vector3 position;
	Vector2 texcoord;

	VertexMesh() :position(0), texcoord(0)
	{
	}
	VertexMesh(Vector3 position, Vector2 texcoord) :position(position), texcoord(texcoord)
	{
	}

	VertexMesh(const VertexMesh& vertex) :position(vertex.position), texcoord(vertex.texcoord)
	{
	}

	~VertexMesh()
	{
	}
};

