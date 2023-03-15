#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);

	void clearRenderTargetColor(SwapChainPtr swap_chain, float r, float g, float b, float a);
	void setVertexBuffer(VertexBufferPtr vertex_buffer);
	void setIndexBuffer(IndexBufferPtr index_buffer);

	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void setViewportSize(UINT width, UINT height);
	
	void setVertexShader(VertexShaderPtr vertex_shader);
	void setPixelShader(PixelShaderPtr pixel_shader);

	void setTexture(VertexShaderPtr pixel_shader, TexturePtr texture);
	void setTexture(PixelShaderPtr pixel_shader, TexturePtr texture);

	void setConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr buffer);
	void setConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr buffer);


	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;

	RenderSystem* m_system = nullptr;

	friend class ConstantBuffer;
};
