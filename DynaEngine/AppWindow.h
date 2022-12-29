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
#include "Vector2.h"

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();

	void updateQuadPosition();

	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onLoseFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void whileKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Vector2& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Vector2& delta_mouse_pos);
	virtual void whileLeftMouseDown(const Vector2& delta_mouse_pos);
	virtual void onLeftMouseUp(const Vector2& delta_mouse_pos);
	virtual void onRightMouseDown(const Vector2& delta_mouse_pos);
	virtual void whileRightMouseDown(const Vector2& delta_mouse_pos);
	virtual void onRightMouseUp(const Vector2& delta_mouse_pos);

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time = 0.0f;

	float m_scale = 0.0f;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
};

