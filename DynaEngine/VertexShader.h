#pragma once

class GraphicsEngine;

class VertexShader
{
public:
	VertexShader();
	bool release();
	~VertexShader();
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11VertexShader* m_vs;
	friend class GraphicsEngine;
};

