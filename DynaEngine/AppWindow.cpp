#include "AppWindow.h"
#include "Vector3.h"
#include "Matrix4x4.h"

#include <Windows.h>

struct vertex
{
	Vector3 position;
	Vector3 color;
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

void AppWindow::updateQuadPosition()
{
	constant cc;

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += m_delta_time / 2.0f;

	Matrix4x4 temp;

	//temp.setTranslation(Vector3::lerp(Vector3(-1.5, -1.5, 0), Vector3(1.5, 1.5, 0), m_delta_pos));
	//cc.m_world.setScale(Vector3::lerp(Vector3(0.5, 0.5, 0), Vector3(1, 1, 0), (sin(m_delta_scale)+1.0f)/2.0f));

	//cc.m_world *= temp;

	cc.m_world.setScale(Vector3(1, 1, 1));

	temp.setIdentity();
	temp.setRotation(Vector3(m_delta_scale, m_delta_scale, m_delta_scale));
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex vertex_list[] =
	{
		{Vector3(-0.5f,-0.5f,-0.5f), Vector3(1.0f,1.0f,1.0f)},
		{Vector3(-0.5f, 0.5f,-0.5f), Vector3(0.3f,0.3f,0.3f)},
		{Vector3( 0.5f, 0.5f,-0.5f), Vector3(1.0f,1.0f,1.0f)},
		{Vector3( 0.5f,-0.5f,-0.5f), Vector3(0.3f,0.3f,0.3f)},
		{Vector3( 0.5f,-0.5f, 0.5f), Vector3(1.0f,1.0f,1.0f)},
		{Vector3( 0.5f, 0.5f, 0.5f), Vector3(0.3f,0.3f,0.3f)},
		{Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f,1.0f,1.0f)},
		{Vector3(-0.5f,-0.5f, 0.5f), Vector3(0.3f,0.3f,0.3f)},
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertex_list, sizeof(vertex), size_vertex_list, shader_byte_code, size_shader);

	unsigned int index_list[] =
	{
		0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 1, 6, 5, 5, 2, 1, 7, 0, 3, 3, 4, 7, 3, 2, 5, 5, 4, 3, 7, 6, 1, 1, 0, 7
	};

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib->load(index_list, size_index_list);
	
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0, 0, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	updateQuadPosition();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta)?((m_new_delta - m_old_delta) / 1000.0f):0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();

	m_vs->release();
	m_ps->release();

	m_swap_chain->release();
	GraphicsEngine::get()->release();
}
