#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);

	void clearRenderTargetColor(SwapChain* swap_chain, float r, float g, float b, float a);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);

	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void setViewportSize(UINT width, UINT height);
	
	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;

	RenderSystem* m_system = nullptr;

	friend class ConstantBuffer;
};
