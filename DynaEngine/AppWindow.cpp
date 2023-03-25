#include "AppWindow.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "Mesh.h"
#include <Windows.h>

struct vertex
{
	Vector3 position;
	Vector2 texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
};

AppWindow::AppWindow()
{
}

void AppWindow::update()
{
	constant cc;

	Matrix4x4 temp;

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();
	
	temp.setIdentity();
	temp.setRotation(Vector3(m_rot_x, m_rot_y, 0));
	world_cam *= temp;

	Vector3 new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);
	
	new_pos = new_pos + world_cam.getXDirection() * (m_sideward * 0.1f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();

	cc.m_view = world_cam;

	RECT windowRect = this->getClientWindowRect();

	int width = (windowRect.right - windowRect.left);
	int height = (windowRect.bottom - windowRect.top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.01f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);
	InputSystem::get()->setCursorVisibility(false);

	m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\white.png");
	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\Monk.obj");

	RECT rc = this->getClientWindowRect();
	m_swap_chain=GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3(0, 0, -2));

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
	
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0, 0, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_wood_tex);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta)?((m_new_delta - m_old_delta) / 1000.0f):0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onLoseFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W') { m_forward += 1.0f; }
	else if (key == 'S') { m_forward -= 1.0f; }
	else if (key == 'A') { m_sideward -= 1.0f; }
	else if (key == 'D') { m_sideward += 1.0f; }
}

void AppWindow::whileKeyDown(int key)
{
}

void AppWindow::onKeyUp(int key)
{
	if (key == 'W') { m_forward -= 1.0f; }
	else if (key == 'S') { m_forward += 1.0f; }
	else if (key == 'A') { m_sideward += 1.0f; }
	else if (key == 'D') { m_sideward -= 1.0f; }
}

void AppWindow::onMouseMove(const Vector2& mouse_pos)
{
	RECT windowRect = this->getClientWindowRect();

	int width = (windowRect.right - windowRect.left);
	int height = (windowRect.bottom - windowRect.top);

	m_rot_x += (mouse_pos.y - (height / 2.0f)) * m_delta_time * 0.1f;
	m_rot_y += (mouse_pos.x - (width / 2.0f)) * m_delta_time * 0.1f;

	InputSystem::get()->setCursorPosition(Vector2((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseDown(const Vector2& mouse_pos)
{
}

void AppWindow::whileLeftMouseDown(const Vector2& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Vector2& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Vector2& mouse_pos)
{
}

void AppWindow::whileRightMouseDown(const Vector2& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Vector2& mouse_pos)
{
}
