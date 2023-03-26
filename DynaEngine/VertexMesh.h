#pragma once
#include <math.h>
#include "Vector3.h"
#include "Vector2.h"

class VertexMesh
{
public:
	Vector3 position;
	Vector2 texcoord;
	Vector3 normal;

	VertexMesh() :position(0), texcoord(0), normal(0)
	{
	}
	VertexMesh(Vector3 position, Vector2 texcoord, Vector3 normal) :position(position), texcoord(texcoord), normal(normal)
	{
	}

	VertexMesh(const VertexMesh& vertex) :position(vertex.position), texcoord(vertex.texcoord), normal(vertex.normal)
	{
	}

	~VertexMesh()
	{
	}
};

