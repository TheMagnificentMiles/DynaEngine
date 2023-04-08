#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class SwapChain
{
public:
	SwapChain(RenderSystem* system, HWND hwnd, UINT width, UINT height);
	void setFullScreen(bool fullscreen, unsigned int width, unsigned int height);
	void resize(unsigned int width, unsigned int height);
	bool present(bool vsync);
	~SwapChain();
private:
	void reloadBuffers(unsigned int width, unsigned int height);

	IDXGISwapChain* m_swap_chain = nullptr;
	ID3D11RenderTargetView* m_rtv = nullptr;
	ID3D11DepthStencilView* m_dsv = nullptr;

	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};

