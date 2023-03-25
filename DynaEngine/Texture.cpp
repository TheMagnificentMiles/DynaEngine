#include "Texture.h"
#include "GraphicsEngine.h"
#include <DirectXTex.h>
#include <exception>

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(GraphicsEngine::get()->getRenderSystem()->m_d3d_device, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);
	}
	else
	{
		throw std::exception("Failed to create Texture");
	}
}

Texture::~Texture()
{
	m_texture->Release();
}
