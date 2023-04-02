#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include "Vector2.h"

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onLoseFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void whileKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Vector2& mouse_pos) override;

	virtual void onLeftMouseDown(const Vector2& mouse_pos);
	virtual void whileLeftMouseDown(const Vector2& mouse_pos);
	virtual void onLeftMouseUp(const Vector2& mouse_pos);
	virtual void onRightMouseDown(const Vector2& mouse_pos);
	virtual void whileRightMouseDown(const Vector2& mouse_pos);
	virtual void onRightMouseUp(const Vector2& mouse_pos);

	void update();
	void updateModel();
	void updateCamera();
	void updateSkybox();
	void drawMesh(const MeshPtr& mesh, const VertexShaderPtr& vs, const PixelShaderPtr& ps, const ConstantBufferPtr& cb, const TexturePtr& tex);

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time = 0.0f;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	float m_light_rot = 0.0f;

	float m_forward = 0.0f;
	float m_sideward = 0.0f;

	bool m_focused = true;

	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	SwapChainPtr m_swap_chain;
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	PixelShaderPtr m_sky_ps;
	ConstantBufferPtr m_cb;
	ConstantBufferPtr m_sky_cb;
	TexturePtr m_wood_tex;
	TexturePtr m_sky_tex;
	MeshPtr m_mesh;
	MeshPtr m_sky_mesh;
};

