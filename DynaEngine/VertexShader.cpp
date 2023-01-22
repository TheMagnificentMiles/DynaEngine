#include "VertexShader.h"
#include "RenderSystem.h"
#include <exception>

VertexShader::VertexShader(RenderSystem* system, const void* shader_byte_code, size_t byte_code_size) : m_system (system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs))) {
		throw std::exception("Failed to create VertexShader");
	}
}

VertexShader::~VertexShader()
{
	m_vs->Release();
}