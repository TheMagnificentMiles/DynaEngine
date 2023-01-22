#include "PixelShader.h"
#include "RenderSystem.h"
#include <exception>

PixelShader::PixelShader(RenderSystem* system, const void* shader_byte_code, size_t byte_code_size) : m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps))) {
		throw std::exception("Failed to create PixelShader");
	}
}

PixelShader::~PixelShader()
{
	m_ps->Release();
}